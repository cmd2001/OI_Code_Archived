#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long int lli;
const int maxn=5e2+1e1,maxe=1e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int u[maxe],v[maxe];
lli in[maxn],len[maxe];
int n,m;

namespace Flow {
    int s[maxn<<1],t[maxe<<3],nxt[maxe<<3];
    lli f[maxe<<3];
    int dep[maxn<<1],st,ed;
    inline void coredge(int from,int to,lli flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,lli flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        std::queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline lli dfs(int pos,lli flow) {
        if( pos == ed ) return flow;
        lli ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],std::min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline lli dinic() {
        lli ret = 0 , now = 0;
        while( bfs() ) while( now = dfs(st,inf) ) ret += now;
        return ret;
    }
}

struct Graph {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],inq[maxn],cnt;
    lli l[maxe<<1],dis[maxn];
    inline void addedge(int from,int to,lli len) {
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void doubledge(int a,int b,lli len) {
        addedge(a,b,len) , addedge(b,a,len);
    }
    inline void spfa(int st) {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        std::queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] ) q.push(t[at]),inq[t[at]] = 1;
            }
        }
    }
}gra,rev;

inline void build() {
    using namespace Flow;
    #define cov(x,t) (x*2-1+t)
    for(int i=1;i<=n;i++) singledge(cov(i,0),cov(i,1),in[i]);
    for(int i=1;i<=m;i++) if( gra.dis[u[i]] + len[i] + rev.dis[v[i]] == gra.dis[n] || gra.dis[v[i]] + len[i] + rev.dis[u[i]] == gra.dis[n] ) {
        singledge(cov(u[i],1),cov(v[i],0),inf) , singledge(cov(v[i],1),cov(u[i],0),inf);
    }
    singledge(st=n*2+1,cov(1,1),inf) , singledge(cov(n,0),ed=st+1,inf);
}

signed main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%lld",u+i,v+i,len+i) , gra.doubledge(u[i],v[i],len[i]) , rev.doubledge(u[i],v[i],len[i]);
    for(int i=1;i<=n;i++) scanf("%lld",in+i);
    gra.spfa(1) , rev.spfa(n) , build() , printf("%lld\n",Flow::dinic());
    return 0;
}