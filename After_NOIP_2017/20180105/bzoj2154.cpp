#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e7+1e2;
const int mod = 20101009;

lli sum[maxn],ss[maxn];
lli n,m;

inline void pre(lli lim) { // don't prepare to maxn.
    static int prime[maxn],cnt;
    static char vis[maxn];
    
    sum[1] = 1;
    for(lli i=2;i<=lim;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i,
            sum[i] = -1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            sum[i*prime[j]] = -sum[i];
            if( ! ( i % prime[j]) ) {
                sum[i*prime[j]] = 0;
                break;
            }
        }
    }
    for(int i=1;i<=lim;i++)
        sum[i] = sum[i] * i * i % mod;
    for(int i=1;i<=lim;i++) {
        sum[i] += sum[i-1],
        sum[i] = ( sum[i] % mod + mod ) % mod;
        ss[i] = ( ss[i-1] + i ) % mod;
    }
}

inline lli fnm(lli n,lli m,lli step) {
    n /= step , m /= step;
    return ( ( n + 1 ) * n >> 1 ) % mod * ( ( ( m + 1 ) * m >> 1 ) % mod ) % mod;
}
inline lli f(lli n,lli m) {
    lli ret = 0 , lim  = min( n , m );
    for(lli i=1,j;i<=lim;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += ( ( sum[j] - sum[i-1] ) % mod + mod ) % mod * fnm(n,m,i) % mod;
        ret = ( ret % mod + mod ) % mod;
    }
    return ret;
}
inline lli getans(lli n,lli m) {
    lli ret = 0 , lim = min( n , m );
    for(lli i=1,j;i<=lim;i=j+1) {
        j = min( n / ( n / i ) ,  m / ( m / i ) );
        ret += ( ( ss[j] - ss[i-1] ) % mod + mod ) % mod * f(n/i,m/i);
        ret = ( ret % mod + mod ) % mod;
    }
    return ret;
}

int main() {
    scanf("%lld%lld",&n,&m);
    pre(min(n,m));
    printf("%lld\n",getans(n,m));
    return 0;
}