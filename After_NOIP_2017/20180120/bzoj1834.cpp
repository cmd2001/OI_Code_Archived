#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
using namespace std;
const int maxn=1e3+1e2,maxm=5e3+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

int st,ed;
lli mxf,ans;

namespace Dinic {
    int s[maxn],t[maxm<<3],nxt[maxm<<3],dep[maxn];
    lli f[maxm<<3];
    
    inline void coredge(int from,int to,lli flow) {
        static int cnt = 1;
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
                if( f[at] && !~dep[t[at]] ) {
                    dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
                }
        }
        return ~dep[ed];
    }
    inline lli dfs(int pos,lli flow) {
        if( pos == ed ) return flow;
        lli ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],min(flow,f[at]));
                ret += now , flow -= now,
                f[at] -= now , f[at^1] += now;
            }
        return ret;
    }
    inline lli dinic() {
        lli ret = 0 , now = 0;
        while( bfs() ) 
            while( now = dfs(st,inf) )
                ret += now;
        return ret;
    }
}

namespace MCMF {
    int s[maxn],t[maxm<<3],nxt[maxm<<3];
    lli dis[maxn];
    lli f[maxm<<3],c[maxm<<3];
    int sou[maxn],inq[maxn];
    
    inline void coredge(int from,int to,lli flow,lli cost) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , c[cnt] = cost,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,lli flow,lli cost) {
        coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
    }
    
    inline bool spfa() {
        memset(dis,0x3f,sizeof(dis)); dis[st] = 0;
        queue<int> q; q.push(st); inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop(); inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                    dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                    if( !inq[t[at]] ) {
                        q.push(t[at]) , inq[t[at]] = 1;
                    }
                }
        }
        return dis[ed] != inf;
    }
    inline lli release() {
        lli ret = inf;
        for(int i=ed;i!=st;i=t[sou[i]^1])
            ret = min( ret ,f[sou[i]] );
        for(int i=ed;i!=st;i=t[sou[i]^1])
            f[sou[i]] -= ret , f[sou[i]^1] += ret;
        return ret;
    }
    inline lli flow() {
        lli ret = 0;
        while( spfa() )
            ret += dis[ed] * release();
        return ret;
    }
}

int main() {
    static int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    st = n + 1 , ed = n + 2;
    for(int i=1,u,v,f,c;i<=m;i++) {
        scanf("%d%d%d%d",&u,&v,&f,&c);
        Dinic::singledge(u,v,f);
        MCMF::singledge(u,v,f,0);
        MCMF::singledge(u,v,inf,c);
    }
    
    Dinic::singledge(st,1,inf);
    Dinic::singledge(n,ed,inf);
    mxf = Dinic::dinic();
    
    MCMF::singledge(st,1,mxf+k,0);
    MCMF::singledge(n,ed,mxf+k,0);
    ans = MCMF::flow();
    
    printf("%lld %lld\n",mxf,ans);
    
    return 0;
}