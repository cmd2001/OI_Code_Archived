#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=1e5+1e2;

int bel[maxn],siz[maxn],iid;
int u[maxn],v[maxn];

namespace Tarjan {
    int s[maxn],t[maxn],nxt[maxn];
    int vis[maxn],dfn[maxn],low[maxn],stk[maxn],ins[maxn],dd,top;
    inline void addedge(int from,int to) {
        static int cnt = 0;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos) {
        vis[pos] = ins[stk[++top]=pos] = 1 , low[pos] = dfn[pos] = ++dd;
        for(int at=s[pos];at;at=nxt[at])
            if( !vis[t[at]] ) dfs(t[at]) , low[pos] = std::min( low[pos] , low[t[at]] );
            else if( ins[t[at]] ) low[pos] = std::min( low[pos] , dfn[t[at]] );
        if( low[pos] == dfn[pos] ) {
            ++iid;
            do ++siz[bel[stk[top]]=iid] , ins[stk[top--]] = 0; while( ins[pos] );
        }
    }
}

struct Graph {
    int s[maxn],t[maxn],nxt[maxn],deg[maxn],f[maxn],cnt;
    Graph() { memset(f,0xef,sizeof(f)); }
    inline void addedge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to];
    }
    inline void topo() {
        std::queue<int> q; f[bel[1]] = siz[bel[1]];
        for(int i=1;i<=iid;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) {
                f[t[at]] = std::max( f[t[at]] , f[pos] + siz[t[at]] );
                if( !--deg[t[at]] ) q.push(t[at]);
            }
        }
    }
}gra,neg;

int main() {
    static int n,m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",u+i,v+i) , Tarjan::addedge(u[i],v[i]);
    for(int i=1;i<=n;i++) if( !Tarjan::vis[i] ) Tarjan::dfs(i);
    for(int i=1;i<=m;i++) if( bel[u[i]] != bel[v[i]] ) gra.addedge(bel[u[i]],bel[v[i]]) , neg.addedge(bel[v[i]],bel[u[i]]);
    gra.topo() , neg.topo();
    ans = siz[bel[1]];
    for(int i=1;i<=m;i++) if( bel[u[i]] != bel[v[i]] ) ans = std::max( ans , neg.f[bel[u[i]]] + gra.f[bel[v[i]]] - siz[bel[1]] );
    printf("%d\n",ans);
    return 0;
}
