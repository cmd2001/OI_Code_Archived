#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=4e6+1e2,lim=4e6;
const int mod = 1 << 30;
 
int mu[maxn],f[maxn];
 
inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    mu[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , mu[i] = -1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( ! ( i % prime[j] ) ) break;
            mu[tar] = -mu[i];
        }
    }
    for(int i=1;i<=lim;i++) if( mu[i] ) {
        for(int j=1;(lli)i*j<=lim;j++) f[i*j] += j * mu[j];
    }
    for(int i=1;i<=lim;i++) f[i] *= i , f[i] += f[i-1];
}
inline int sum(int x) {
    return x * ( x + 1 ) >> 1;
}
inline int calc(int n,int m) {
    if( n > m ) swap(n,m);
    int ret = 0;
    for(int l=1,r;l<=n;l=r+1) {
        r = min( n / ( n / l ) , m / ( m / l ) );
        ret += ( f[r] - f[l-1] ) * sum(n/l) * sum(m/l);
    }
    return ret;
}
 
int main() {
    static int T,a,b;
    static lli ans;
    scanf("%d",&T) , sieve();
    while(T--) {
        scanf("%d%d",&a,&b) , ans = calc(a,b);
        ans = ( ans % mod + mod ) % mod;
        printf("%lld\n",ans);
    }
    return 0;
}

