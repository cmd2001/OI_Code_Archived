#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2,mod=998244353,rev=499122177;

double x;
lli mu[maxn];
int n,m;

inline void sieve() {
    static int prime[maxn],cnt;
    static char vis[maxn];
    
    mu[1] = 1;
    for(lli i=2;i<maxn;i++) {
        if( !vis[i] )
            prime[++cnt] = i ,
            mu[i] = -1;
        for(int j=1;j<=cnt&&i*prime[j]<maxn;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( ! ( i % prime[j] ) )
                break;
            mu[tar] = -mu[i];
        }
    }
}

inline lli sum(int x) {
    return ( ( (lli) x ) * ( x + 1 ) >> 1 ) % mod;
}
inline lli sq(lli x) {
    return x * x % mod;
}
inline lli calc(int d) {
    lli ret = 0;
    for(lli t=n/d;t;t--) {
        lli a = n / ( d * t ) , b = m / ( d * t );
        ret += mu[t] * ( sum(a) * sum(b) % mod * sq( d * t % mod ) % mod 
        - sum(a) * d % mod * t % mod * b % mod 
        - sum(b) * d % mod * t % mod * a % mod 
        + a * b % mod * d % mod * 2 % mod * ( (lli) ( x / d ) ) % mod
        + a * b % mod * d % mod );
        ret = ( ret % mod + mod ) % mod;
    }
    return ret;
}
inline lli getans() {
    lli ret = 0;
    for(int i=1;i<=n;i++) {
        ret += calc(i) ,
        ret %= mod;
    }
    return ( ret + mod ) % mod;
}

int main() {
    sieve();
    scanf("%d%d%lf",&n,&m,&x);
    if( n > m )
        swap(n,m);
    printf("%lld\n",getans()*rev%mod);
    return 0;
}
