#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=5e7+1e2,lim=5e7;
const int mod=998244353;

namespace Sieve {
    lli phi[maxn];
    inline void sieve() {
        static int prime[maxn/10],cnt;
        static bool vis[maxn];
        phi[1] = 1;
        for(int i=2;i<=lim;i++) {
            if( !vis[i] ) prime[++cnt] = i , phi[i] = i - 1;
            for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
                const int t = i * prime[j];
                vis[t] = 1;
                if( i % prime[j] ) phi[t] = phi[i] * ( prime[j] - 1 );
                else { phi[t] = phi[i] * prime[j]; break; }
            }
        }
        for(int i=1;i<=lim;i++) phi[i] = ( phi[i] + phi[i-1] ) % mod;
    }
    unordered_map<lli,lli> mp;
    inline lli calc(lli x) {
        if( x <= lim ) return phi[x];
        if( mp.find(x) != mp.end() ) return mp[x];
        lli ret = ( ( x % mod ) * ( x % mod + 1 ) >> 1 ) % mod;
        for(lli i=2,j;i<=x;i=j+1) {
            j = x / ( x / i );
            ret -= ( j - i + 1 ) % mod * calc( x / i ) % mod , ret %= mod;
        }
        return mp[x] = ( ret + mod ) % mod;
    }
}

inline lli fastpow(lli base,lli tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline lli supow(lli x,lli inv,lli n) {
    if( x == 1 ) return n;
    lli t = ( fastpow(x,n+1) - 1 + mod ) % mod;
    return t * inv % mod;
}
inline lli calc(lli x,lli n) {
    const lli inv = fastpow(x-1,mod-2);
    lli ret = 0;
    for(lli i=1,j;i<=n;i=j+1) {
        j = n / ( n / i );
        ret += ( supow(x,inv,j) - supow(x,inv,i-1) + mod ) % mod * ( ( 2 * Sieve::calc(n/i) % mod - 1 + mod ) % mod ) % mod , ret %= mod;
    }
    return ret;
}


int main() {
    static int T;
    static lli n,a,b;
    scanf("%d",&T) , Sieve::sieve();
    while(T--) scanf("%lld%lld%lld",&n,&a,&b) , printf("%lld\n",(calc(a,n)-calc(b,n)+mod)%mod);
    return 0;
}
