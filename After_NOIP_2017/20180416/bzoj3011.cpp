#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=2e5+1e2;

struct Heap {
    lli dat[maxn],lazy[maxn];
    int lson[maxn],rson[maxn],dep[maxn],cnt;
    inline void apply(int pos,lli x) {
        if( !pos ) return;
        dat[pos] += x , lazy[pos] += x;
    }
    inline void push(int pos) {
        if( lazy[pos] ) apply(lson[pos],lazy[pos]) , apply(rson[pos],lazy[pos]) , lazy[pos] = 0;
    }
    inline int merge(int x,int y) {
        if( ! ( x && y ) ) return x | y;
        if( dat[x] < dat[y] ) swap(x,y); // Big root heap .
        push(x) , push(y) , rson[x] = merge(rson[x],y);
        if( dep[lson[x]] < dep[rson[x]] ) swap(lson[x],rson[x]);
        dep[x] = dep[rson[x]] + 1;
        return x;
    }
    inline lli top(int x) {
        return dat[x];
    }
    inline void pop(int &x) {
        push(x) , x = merge(lson[x],rson[x]);
    }
    inline void push(int &x,lli t) {
        dat[++cnt] = t , x = merge(x,cnt);
    }
    inline void add(int x,lli t) {
        apply(x,t);
    }
}h;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
lli l[maxn<<1],lim;
int root[maxn],siz[maxn];

inline void addedge(int from,int to,lli len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    siz[pos] = 1 , h.push(root[pos],0);
    for(int at=s[pos];at;at=nxt[at]) dfs(t[at]) , h.add(root[t[at]],l[at]) , root[pos] = h.merge(root[pos],root[t[at]]) , siz[pos] += siz[t[at]];
    while( siz[pos] && h.top(root[pos]) > lim ) h.pop(root[pos]) , --siz[pos];
}

int main() {
    static int n;
    static lli len;
    scanf("%d%lld",&n,&lim);
    for(int i=2,fa;i<=n;i++) scanf("%d%lld",&fa,&len) , addedge(fa,i,len);
    dfs(1);
    for(int i=1;i<=n;i++) printf("%d\n",siz[i]);
    return 0;
}
