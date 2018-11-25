#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long int lli;
using namespace std;
const int maxn=4e2+1e1,maxe=4e3+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;
const int int_inf=0x3f3f3f3f;

int in[maxn],u[maxe],v[maxe],c[maxe];
int n,m;
lli ans;
bool flag;

struct Graph {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],cnt,st,ed;
    lli l[maxe<<1],dis[maxn];
    bool inq[maxn];
    const lli& operator [] (const int &x) const { return dis[x]; }
    inline void coredge(int from,int to,int len) {
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void spfa() {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
        }
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , cnt = 0;
    }
}gra,rev;

namespace NetworkFlow {
    int s[maxn+maxe],t[maxe<<4],nxt[maxe<<4],fr[maxe<<4],cnt;
    lli f[maxe<<4];
    int dep[maxn+maxe],st,ed;
    inline void coredge(int from,int to,lli flow) {
        t[++cnt] = to , fr[cnt] = from , f[cnt] = flow;
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
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
            }
        }
        return ~dep[ed];
    }
    inline lli dfs(int pos,lli flow) {
        if( pos == ed ) return flow;
        lli ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at]));
            ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline lli dinic() {
        lli ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
    int dfn[maxn+maxe],low[maxn+maxe],bel[maxn+maxe],stk[maxn+maxe],ins[maxn+maxe],top,dd,bb;
    inline void tarjan(int pos) {
        low[pos] = dfn[pos] = ++dd , ins[stk[++top]=pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] ) {
            if( !dfn[t[at]] ) tarjan(t[at]) , low[pos] = min( low[pos] , low[t[at]] );
            else if( ins[t[at]] ) low[pos] = min( low[pos] , dfn[t[at]] );
        }
        if( low[pos] >= dfn[pos] ) {
            ++bb;
            do bel[stk[top]] = bb , ins[stk[top--]] = 0; while( ins[pos] );
        }
    }
    inline void getans() {
        ans = dinic() , flag = 1;
        for(int i=1;i<=n+m;i++) if( !dfn[i] ) tarjan(i);
        for(int i=2;i<=cnt;i+=2) if( !f[i] && bel[fr[i]] != bel[t[i]] ) {
            if( bel[fr[i]] != bel[st] || bel[t[i]] != bel[ed] ) flag = 0;
        }
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , memset(dfn,0,sizeof(dfn)) , cnt = 1 , top = dd = bb = 0;
    }
}

inline int cov(int x) {
    return n + x;
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m) , gra.reset() , rev.reset() , NetworkFlow::reset();
        in[n] = int_inf; for(int i=1;i<n;i++) scanf("%d",in+i);
        for(int i=1;i<=m;i++) {
            scanf("%d%d%d",u+i,v+i,c+i);
            gra.addedge(u[i],v[i],c[i]) , rev.addedge(u[i],v[i],c[i]);
        }
        NetworkFlow::st = rev.ed = gra.st = 1 , NetworkFlow::ed = rev.st = gra.ed = n;
        gra.spfa() , rev.spfa();
        for(int i=1;i<=m;i++) {
            if( gra[n] == gra[u[i]] + rev[v[i]] + c[i] ) {
                NetworkFlow::singledge(u[i],cov(i),in[u[i]]);
                NetworkFlow::singledge(cov(i),v[i],in[v[i]]);
            } else if( gra[n] == gra[v[i]] + rev[u[i]] + c[i] ) {
                NetworkFlow::singledge(v[i],cov(i),in[v[i]]);
                NetworkFlow::singledge(cov(i),u[i],in[u[i]]);
            }
        }
        NetworkFlow::getans() , printf("%s %lld\n",flag?"Yes":"No",ans);
    }
    return 0;
}

