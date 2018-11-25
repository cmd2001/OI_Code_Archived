#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
using namespace std;
const int maxn=4e3+1e2,maxe=6e4+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int u[maxe],v[maxe],cov[maxe],id[maxn];
bool must[maxe],can[maxe];
int n,m,st,ed;

namespace Flow {
    int s[maxn],t[maxe<<2],nxt[maxe<<2],dep[maxn],cnt=1;
    lli f[maxe<<2];
    int low[maxn],dfn[maxn],stk[maxn],ins[maxn],vis[maxn],top,iid,dd;
    inline void coredge(int from,int to,lli flow) {
        t[++cnt] = to , f[cnt] = flow ,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,lli flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && !~dep[t[at]] )
                    dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline lli dfs(int pos,lli flow) {
        if( pos == ed ) return flow;
        lli ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],min(flow,f[at]));
                ret += now , flow -= now ,
                f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline lli dinic() {
        lli ret = 0 , now = 0;
        while( bfs() ) {
            while( ( now = dfs(st,inf) ) )
                ret += now;
        }
        return ret;
    }
    inline void tarjan(int pos) {
        vis[pos] = 1;
        low[pos] = dfn[pos] = ++dd;
        stk[++top] = pos , ins[pos] = 1;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] ) {
                if( !vis[t[at]] ) tarjan(t[at]) , low[pos] = min( low[pos] , low[t[at]] );
                else if( ins[t[at]] ) low[pos] = min( low[pos] , dfn[t[at]] );
            }
        if( low[pos] == dfn[pos] ) {
            ++iid;
            do {
                const int x = stk[top--]; ins[x] = 0;
                id[x] = iid;
            } while( ins[pos] ) ;
        }
    }
    inline void work() {
        for(int i=1;i<=n;i++) if( !vis[i] ) tarjan(i);
    }
}

inline void getans() {
    using Flow::f;
    for(int i=1;i<=m;i++)
        if( (!f[cov[i]]) && id[u[i]] != id[v[i]] ) {
            can[i] = 1;
            if( id[st] == id[u[i]] && id[v[i]] == id[ed] ) must[i] = 1;
        }
}

int main() {
    scanf("%d%d%d%d",&n,&m,&st,&ed);
    for(int i=1,f;i<=m;i++) {
        scanf("%d%d%d",u+i,v+i,&f);
        Flow::singledge(u[i],v[i],f) , cov[i] = Flow::cnt - 1;
    }
    Flow::dinic();
    Flow::work();
    getans();
    for(int i=1;i<=m;i++) printf("%d %d\n",can[i],must[i]);
    return 0;
}


