#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long int lli;
using namespace std;
const int maxn=1e3+1e2,maxe=2e3+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

namespace Flow {
    int s[maxn<<1],t[maxe<<2],nxt[maxe<<2],cnt=1;
    lli f[maxe<<2];
    int dep[maxn],st,ed;
    
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
            while( now = dfs(st,inf) ) {
                if( now == inf ) return -1; //No solution .
                ret += now;
            }
        }
        return ret;
    }
    inline void reset(int n) {
        memset(s,0,sizeof(s))  ,cnt = 1;
        st = 1 , ed = n;
    }
}

struct Graph {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],vis[maxn],cnt;
    
    inline void addedge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos) {
        if( vis[pos] ) return;
        vis[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) dfs(t[at]);
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , memset(vis,0,sizeof(vis)) , cnt = 0;
    }
}gra,inv;

int x[maxe],y[maxe],f[maxe];

inline void build(int m) {
    for(int i=1;i<=m;i++) {
        Flow::singledge(x[i],y[i],f[i]);
        if( gra.vis[x[i]] && inv.vis[y[i]] ) Flow::singledge(y[i],x[i],inf);
    }
}

inline void reset(int n) {
    Flow::reset(n);
    gra.reset() , inv.reset();
}

int main() {
    static int T,n,m;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m) , reset(n);
        for(int i=1;i<=m;i++) {
            scanf("%d%d%d",x+i,y+i,f+i);
            gra.addedge(x[i],y[i]) , inv.addedge(y[i],x[i]);
        }
        gra.dfs(1) , inv.dfs(n);
        build(m);
        printf("%lld\n",Flow::dinic());
    }
    return 0;
}
