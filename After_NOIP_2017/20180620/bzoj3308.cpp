#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long int lli;
const int maxn=2e5+1e2;
const int inf=0x3f3f3f3f;

int n,fs;
lli ans;

namespace NetworkFlow {
    int s[maxn],t[maxn<<4],nxt[maxn<<4],f[maxn<<4],c[maxn<<4];
    int dis[maxn],sou[maxn],inq[maxn],st,ed;
    inline void coredge(int from,int to,int flow,int cost) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , c[cnt] = cost , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow,int cost) {
        coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
    }
    inline bool spfa() {
        memset(dis,0xef,fs<<2) , dis[st] = 0;
        queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
        }
        return dis[ed] > 0;
    }
    inline int release() {
        int ret = inf;
        for(int i=ed;i!=st;i=t[sou[i]^1]) ret = min( ret , f[sou[i]] );
        for(int i=ed;i!=st;i=t[sou[i]^1]) f[sou[i]] -= ret , f[sou[i]^1] += ret;
        return ret;
    }
    inline lli flow() {
        lli ret = 0;
        while( spfa() ) ret += dis[ed] * release();
        return ret;
    }
}

namespace Build {
    int prime[maxn],cnt;
    inline void sieve() {
        static bool vis[maxn];
        for(int i=2;i<=n;i++) {
            if( !vis[i] ) prime[++cnt] = i;
            for(int j=1;j<=cnt&&(lli)i*prime[j]<=n;j++) {
                vis[i*prime[j]] = 1;
                if( ! ( i % prime[j] ) ) break;
            }
        }
    }
    inline int calc(int n,int x) {
        int ret = 1;
        while( n >= x ) n /= x , ret *= x;
        return ret;
    }
    inline void build() {
        int i;
        using NetworkFlow::st; using NetworkFlow::ed;
        sieve() , st = cnt + 1 , ed = cnt + 2 , fs = ed + 1;
        for(i=1;i<=cnt&&prime[i]*2<=n;i++) {
            if( (lli) prime[i] * prime[i] <= n ) NetworkFlow::singledge(st,i,1,0) , ans += calc(n,prime[i]);
            else NetworkFlow::singledge(i,ed,1,0) , ans += prime[i];
        }
        while( i <= cnt ) ans += prime[i++];
        for(i=1;i<=cnt&&(lli)prime[i]*prime[i]<=n;i++) ;
        for(;i<=cnt;i++) for(int j=1;(lli)prime[i]*prime[j]<=n;j++) {
            int cal = calc(n/prime[i],prime[j]) * prime[i] , t = calc(n,prime[j]) + prime[i];
            if( cal > t ) NetworkFlow::singledge(j,i,1,cal-t);
        }
    }
}

int main() {
    scanf("%d",&n) , ans = 1 , Build::build() , ans += NetworkFlow::flow() , printf("%lld\n",ans);
    return 0;
}

