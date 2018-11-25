#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=3e5+1e2;

namespace Heap {
    struct Node {
        lli val;
        int id;
        friend Node operator * (const Node &a,const lli &b) {
            return (Node){a.val*b,a.id};
        }
        friend Node operator + (const Node &a,const lli &b) {
            return (Node){a.val+b,a.id};
        }
        friend bool operator > (const Node &a,const Node &b) {
            return a.val > b.val;
        }
    }dat[maxn];
    int lson[maxn],rson[maxn],dep[maxn],cnt;
    lli mul[maxn],add[maxn];
    
    inline void apply(const int &pos,const lli &m,const lli &a) {
        if( !pos ) return;
        dat[pos] = dat[pos] * m + a;
        mul[pos] = mul[pos] * m , add[pos] = add[pos] * m + a;
    }
    inline void push(const int &pos) {
        if( add[pos] || mul[pos] != 1 ) {
            apply(lson[pos],mul[pos],add[pos]);
            apply(rson[pos],mul[pos],add[pos]);
            mul[pos] = 1 , add[pos] = 0;
        }
    }
    inline int merge(int a,int b) {
        if( ! ( a && b ) ) return a | b;
        push(a) , push(b);
        if( dat[a] > dat[b] ) swap(a,b);
        rson[a] = merge(rson[a],b);
        if( dep[lson[a]] < dep[rson[a]] ) swap(lson[a],rson[a]);
        dep[a] = dep[rson[a]] + 1;
        return a;
    }
    inline void insert(int &a,const Node &val) {
        dat[++cnt] = val , mul[cnt] = 1 , add[cnt] = 0;
        a = merge(a,cnt);
    }
    inline void pop(int &a) {
        push(a) , a = merge(lson[a],rson[a]);
    }
    inline Node top(const int &a) {
        return dat[a];
    }
}

int s[maxn],t[maxn],nxt[maxn],root[maxn],dep[maxn];
int tpe[maxn],sumdie[maxn],midep[maxn],st[maxn];
lli v[maxn],c[maxn];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) { // we have pushed inital Nodes.
    for(int at=s[pos];at;at=nxt[at]) {
        dep[t[at]] = dep[pos] + 1 , dfs(t[at]);
        root[pos] = Heap::merge(root[pos],root[t[at]]);
    }
    while( root[pos] && Heap::top(root[pos]).val < c[pos] ) {
        midep[Heap::top(root[pos]).id] = dep[pos] , ++sumdie[pos];
        Heap::pop(root[pos]);
    }
    if( !tpe[pos] ) Heap::apply(root[pos],1,v[pos]);
    else Heap::apply(root[pos],v[pos],0);
}

int main() {
    static int n,m;
    static lli t;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",c+i);
    for(int i=2,f;i<=n;i++) scanf("%d%d%lld",&f,tpe+i,v+i) , addedge(f,i);
    for(int i=1;i<=m;i++) {
        scanf("%lld%d",&t,st+i);
        Heap::insert(root[st[i]],(Heap::Node){t,i});
    }
    dep[1] = 1 , dfs(1);
    for(int i=1;i<=n;i++) printf("%d\n",sumdie[i]);
    for(int i=1;i<=m;i++) printf("%d\n",dep[st[i]]-midep[i]);
    return 0;
}


