#include<cstdio>
#include<algorithm>
#include<cmath>
#define bool unsigned char
typedef long long int lli;
const int maxn=5e4+1e2;

int mu[maxn],n,sq;

inline lli calc(int n,int x) {
    lli ret = 0;
    for(int i=1;i<=x;i++) {
        int t = n / i;
        for(int su=i+1,last;su<(i<<1)&&su<=t;su=last+1) {
            last = std::min( ( i << 1 ) - 1 , t / ( t / su ) );
            ret += ( last - su + 1 ) * ( t / su );
        }
    }
    return ret;
}

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    mu[1] = 1;
    for(int i=2;i<=sq;i++) {
        if( !vis[i] ) prime[++cnt] = i , mu[i] = -1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=sq;j++) {
            const int tar = i * prime[j]; vis[tar] = 1;
            if( i % prime[j] ) mu[tar] = -mu[i];
            else break;
        }
    }
}


int main() {
    static lli ans;
    scanf("%d",&n) , sq = std::sqrt(n) , sieve();
    for(int i=1;i<=sq;i++) ans += calc(n/i/i,sq/i) * mu[i];
    printf("%lld\n",ans);
    return 0;
}

