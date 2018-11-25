#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int mod=19940417;

inline lli fastpow(lli base,lli tim,lli mod) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline lli sums(lli x) {
    return ( x * ( x + 1 ) >> 1 ) % mod;
}
inline lli sumc(lli x) {
    static const lli inv=3323403;
    return x * ( x + 1 ) % mod * ( 2 * x + 1 ) % mod * inv % mod;
}

inline lli calcmul(lli t) {
    lli ret = 0;
    for(lli i=1,j;i<=t;i=j+1) {
        j = t / ( t / i );
        ret += ( t / i ) * ( sums(j) - sums(i-1) ) % mod , ret %= mod;
    }
    return ( ret + mod ) % mod;
}
inline lli calcmulmul(lli n,lli m) {
    lli ret = 0;
    if( m < n ) swap( m , n );
    for(lli i=1,j;i<=n;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += ( n / i ) * ( m / i ) % mod * ( sumc(j) - sumc(i-1) ) % mod , ret %= mod;
    }
    return ( ret + mod ) % mod;
}
inline lli calcmin(lli n,lli m) {
    lli ret = 0;
    if( m < n ) swap( m , n );
    for(lli i=1,j;i<=n;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += (  m * ( n / i ) % mod + n * ( m / i ) % mod ) % mod * ( sums(j) - sums(i-1) ) % mod , ret %= mod;
    }
    return ( ret + mod ) % mod;
}
inline lli calca(lli n,lli m) {
    lli ret = ( n * n % mod - calcmul(n) ) % mod * ( m * m % mod - calcmul(m) ) % mod;
    return ( ret + mod ) % mod;
}
inline lli calcb(lli n,lli m) {
    if( m < n ) swap(n,m);
    lli ret = n * n % mod * m % mod;
    ret -= calcmin(n,m) , ret %= mod;
    ret += calcmulmul(n,m) , ret %= mod;
    return ( ret + mod ) % mod;
}

int main() {
    static lli n,m,ans;
    scanf("%lld%lld",&n,&m);
    ans = ( calca(n,m) - calcb(n,m) + mod ) % mod;
    printf("%lld\n",ans);
    return 0;
}