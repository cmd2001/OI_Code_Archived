#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e3+1e2,maxe=1e4+1e2;
const int inf=0x3f3f3f3f;

int bel[maxn],iid,st,ed,ss;
int u[maxe],v[maxe],ina[maxn],inb[maxn],a,b,m;

namespace Tarjan {
    int s[maxn],t[maxe],nxt[maxe],cnt;
    int dfn[maxn],low[maxn],ins[maxn],stk[maxn],top,dd;
    
    inline void addedge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos) {
        ins[stk[++top]=pos] = 1 , low[pos] = dfn[pos] = ++dd;
        for(int at=s[pos];at;at=nxt[at])
            if( !dfn[t[at]] ) dfs(t[at]) , low[pos] = min( low[pos] , low[t[at]] );
            else if( ins[t[at]] ) low[pos] = min( low[pos] , dfn[t[at]] );
        if( low[pos] == dfn[pos] ) {
            ++iid;
            do bel[stk[top]] = iid , ins[stk[top--]] = 0; while( ins[pos] );
        }
    }
    inline void reset() {
        memset(dfn,0,sizeof(dfn)) , memset(s,0,sizeof(s)) , cnt = top = dd = 0;
    }
}

namespace Flow {
    int s[maxn],t[maxe<<4],nxt[maxe<<4],f[maxe<<4],c[maxe<<4],cnt;
    int dis[maxn],sou[maxn],inq[maxn];
    
    inline void coredge(int from,int to,int flow,int cost) {
        t[++cnt] = to , f[cnt] = flow , c[cnt] = cost , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow,int cost) {
        coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
    }
    inline bool spfa() {
        memset(dis,0xef,sizeof(dis)) , dis[st] = 0;
        queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                    dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                    if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
                }
        }
        return dis[ed] != *dis;
    }
    inline int release() {
        int ret = inf;
        for(int i=ed;i!=st;i=t[sou[i]^1]) ret = min( ret , f[sou[i]] );
        for(int i=ed;i!=st;i=t[sou[i]^1]) f[sou[i]] -= ret , f[sou[i]^1] += ret;
        return ret;
    }
    inline void flow(int &cst,int &rel) {
        singledge(st,ss,1,0) , cst = rel = 0;
        while( spfa() ) {
            if( !dis[ed] ) break;
            cst += dis[ed] * release() , ++rel;
            singledge(st,ss,1,0);
        }
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , cnt = 1;
    }
}

inline void build() {
    using namespace Flow;
    st = iid * 2 + 1 , ed = st + 1 , ss = ed + 1;
    #define cov(x,t) (x*2-1+t)
    for(int i=1;i<=iid;i++) singledge(cov(i,0),cov(i,1),1,1) , singledge(cov(i,0),cov(i,1),inf,0);
    for(int i=1;i<=m;i++) if( bel[u[i]] != bel[v[i]] ) singledge(cov(bel[u[i]],1),cov(bel[v[i]],0),inf,0);
    for(int i=1;i<=a;i++) singledge(ss,cov(bel[ina[i]],0),inf,0);
    for(int i=1;i<=b;i++) singledge(cov(bel[inb[i]],1),ed,inf,0);
}

inline void reset() {
    Tarjan::reset() , Flow::reset();
    memset(bel,0,sizeof(bel)) , iid = 0;
}

int main() {
    static int T,n,cst,rel;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d%d",&n,&m,&a,&b) , reset();
        for(int i=1;i<=a;i++) scanf("%d",ina+i);
        for(int i=1;i<=b;i++) scanf("%d",inb+i);
        for(int i=1;i<=m;i++) scanf("%d%d",u+i,v+i) , Tarjan::addedge(u[i],v[i]);
        for(int i=1;i<=n;i++) if( !Tarjan::dfn[i] ) Tarjan::dfs(i);
        build() , Flow::flow(cst,rel);
        if( cst != iid ) puts("no solution");
        else printf("%d\n",rel);
    }
    return 0;
}
