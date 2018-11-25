#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define bool unsigned char
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e1,lim=1e6;
const int mod = 1e9 + 7;

namespace Inv {
    inline lli getinv(lli x) {
        lli ret = 1 , tme = mod - 2;
        while( tme ) {
            if( tme & 1 ) ret = ret * x % mod;
            x = x * x % mod;
            tme >>= 1;
        }
        return ret;
    }
}
const int inv2 = Inv::getinv(2) , inv6 = Inv::getinv(6);

lli sum[maxn],me[maxn];
bool vis[maxn];
lli n;

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    sum[1] = 1;
    for(lli i=2;i<=lim;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i , sum[i] = i - 1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( ! ( i % prime[j] ) ) {
                sum[tar] = sum[i] * prime[j] % mod;
                break;
            }
            sum[tar] = sum[i] * ( prime[j] - 1 ) % mod;
        }
    }
    for(int i=1;i<=lim;i++)
        sum[i] = sum[i] * i % mod ,
        sum[i] = ( sum[i] + sum[i-1] ) % mod;
}

inline lli sumsquare(lli x) {
    return x * ( x + 1 ) % mod * ( x * 2 + 1 ) % mod * inv6 % mod;
}
inline lli sumline(lli x) {
    return ( x + 1 ) * x % mod * inv2 % mod;
}
inline lli segment(lli st,lli ed) {
    return ( sumline(ed) - sumline(st) + mod ) % mod;
}
inline lli calc(lli x) {
    if( x <= lim ) return sum[x];
    const int t = n / x;
    if( vis[t] ) return me[t];
    me[t] = sumsquare(x);
    for(lli i=2,j;i<=x;i=j+1) {
        j = x / ( x / i );
        me[t] -= segment(i-1,j) * calc( x / i ) % mod,
        me[t] %= mod;
    }
    me[t] = ( me[t] + mod ) % mod;
    vis[t] = 1;
    return me[t];
}

int main() {
    scanf("%lld",&n);
    sieve();
    
    printf("1\n%lld\n",calc(n));
    
    return 0;
}


