#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
const int maxn=6e3+1e2,maxe=1e7+1e2,maxl=2e5+1e2,lim=2e5;
const int inf=0x3f3f3f3f;

int in[maxn>>1];
unsigned char vis[maxl];
int n,top,st,ed,ans;

namespace Flow {
    int s[maxn],cur[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2];
    int dep[maxn];
    
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow ,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
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
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=cur[pos]?cur[pos]:s[pos];at;at=nxt[at]) {
            cur[pos] = at;
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],std::min(flow,f[at]));
                ret += now , flow -= now ,
                f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0 , now = 0;
        while( bfs() ) {
            memset(cur,0,sizeof(cur));
            while( now = dfs(st,inf) ) ret += now;
        }
        return ret;
    }
}

inline void sieve() {
    static int prime[maxl],cnt;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&(long long)i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}
inline void build() {
    std::sort(in+1,in+n+1);
    for(top=1;top<=n&&in[top]==1;top++) ;
    top = std::max( top - 1 , 1 ) , st = n * 2 + 1 , ed = st + 1;
    #define cov(x) (x+n)
    using Flow::singledge;
    for(int i=top;i<=n;i++)
        for(int j=top+1;j<=n;j++)
            if( !vis[in[i]+in[j]] ) {
                singledge(i,cov(j),1) , singledge(j,cov(i),1);
            }
    for(int i=top;i<=n;i++) {
        singledge(st,i,1) , singledge(cov(i),ed,1);
    }
    ans = n - top + 1;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    sieve() , build();
    ans -= (Flow::dinic()>>1);
    printf("%d\n",ans);
    return 0;
}
