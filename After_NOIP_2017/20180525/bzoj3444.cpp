#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<set>
typedef long long int lli;
const int maxn=5e5+1e2,mod=989381;

struct Edge {
    int u,v;
    Edge() {}
    Edge(int uu,int vv) { u = std::min(uu,vv) , v = std::max(uu,vv); }
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.u != b.u ? a.u < b.u : a.v < b.v;
    }
};

std::set<Edge> es;
int s[maxn],t[maxn<<1],nxt[maxn<<1],deg[maxn],vis[maxn];
int n,m,su,siz,fail;
lli ans;

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a) , ++deg[a] , ++deg[b];
}
inline void dfs(int pos,int fa) {
    siz += vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        if( !vis[t[at]] ) dfs(t[at],pos);
        else fail = 1;
    }
}

int main() {
    scanf("%d%d",&n,&m) , ans = 1;
    for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v) , es.insert(Edge(u,v));
    for(std::set<Edge>::iterator it=es.begin();it!=es.end();it++) addedge(it->u,it->v);
    for(int i=1;i<=n;i++) if( deg[i] > 2 ) return puts("0"),0;
    for(int i=1;i<=n;i++) if( !vis[i] ) {
        siz = 0 , dfs(i,-1) , ++su;
        if( fail ) return puts("0"),0;
        ans = ans * ( 1 + ( siz > 1 ) ) % mod;
    }
    for(int i=1;i<=su;i++) ans = ans * i % mod;
    printf("%lld\n",ans);
    return 0;
}
