#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1e5+1e2;

int s[maxn],t[maxn],nxt[maxn];

int siz[maxn],root[maxn],cost[maxn];
lli su[maxn],val[maxn],ans,lim,mas;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
namespace Heap {
    int lson[maxn],rson[maxn],dis[maxn],val[maxn],cnt;
    inline int merge(int a,int b) {
        if( ! ( a && b ) ) return a | b;
        if( val[a] < val[b] ) std::swap(a,b); // Big root heap .
        rson[a] = merge(rson[a],b);
        if( dis[lson[a]] < dis[rson[a]] ) std::swap(lson[a],rson[a]);
        dis[a] = dis[rson[a]] + 1;
        return a;
    }
    inline int top(const int &x) {
        return val[x];
    }
    inline void pop(int &x) {
        x = merge(lson[x],rson[x]);
    }
    inline void push(int &a,const int &v) {
        val[++cnt] = v , a = merge(a,cnt);
    }
}

inline void dfs(int pos) {
    Heap::push(root[pos],cost[pos]) , siz[pos] = 1 , su[pos] = cost[pos];
    for(int at=s[pos];at;at=nxt[at]) {
        dfs(t[at]);
        root[pos] = Heap::merge(root[pos],root[t[at]]) ,
        siz[pos] += siz[t[at]] , su[pos] += su[t[at]];
    }
    while( siz[pos] && su[pos] > lim ) {
        su[pos] -= Heap::top(root[pos]) , --siz[pos];
        Heap::pop(root[pos]);
    }
    ans = std::max( ans , val[pos] * siz[pos] );
}

int main() {
    static int n;
    scanf("%d%lld",&n,&lim);
    for(int i=1,f;i<=n;i++) {
        scanf("%d%d%lld",&f,cost+i,val+i);
        if( !f ) mas = i;
        else addedge(f,i);
    }
    dfs(mas) , printf("%lld\n",ans);
    return 0;
}
