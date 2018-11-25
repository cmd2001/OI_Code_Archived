#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long int lli;
const int maxn=3e3+1e2,maxe=3e6+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

namespace Flow {
    int s[maxn],t[maxe<<1],nxt[maxe<<1];
    lli f[maxe<<1];
    int dep[maxn],st,ed;
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
                now = dfs(t[at],std::min(flow,f[at])) ,
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
}

int main() {
    using namespace Flow;
    static int n,m;
    static lli ans;
    scanf("%d",&n) , st = n + 1 , ed = n + 2;
    #define cov(x,t) (x*2-1+t+n+2)
    for(int i=1,a;i<=n;i++) scanf("%d",&a) , singledge(st,i,a) , ans += a;
    for(int i=1,b;i<=n;i++) scanf("%d",&b) , singledge(i,ed,b) , ans += b;
    scanf("%d",&m);
    for(int i=1,l,r,o,h,s,t;i<=m;i++) {
        o = cov(i,0) , h = cov(i,1) , scanf("%d%d%d",&s,&l,&r) , ans += l , ans += r;
        singledge(st,o,l) , singledge(h,ed,r);
        while(s--) scanf("%d",&t) , singledge(o,t,inf) , singledge(t,h,inf);
    }
    ans -= dinic() , printf("%lld\n",ans);
    return 0;
}
