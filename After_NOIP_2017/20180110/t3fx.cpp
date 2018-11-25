#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e6+1e2,lim=5e6;
const int mod=1e9+7;
const int muls[6][7] = {
    {0,0,0,0,0,0,0},
    {0,500000004,500000004,0,0,0,0},
    {0,166666668,500000004,333333336,0,0,0},
    {0,0,250000002,500000004,250000002,0,0},
    {0,766666672,0,333333336,500000004,400000003,0},
    {0,0,916666673,0,416666670,500000004,166666668}
};

lli sum[maxn],mem[maxn];
unsigned char vis[maxn];
lli n;
int k;

inline lli gk(lli x) {
    x %= mod;
    lli ret = 0 , now = 1;
    for(int i=0;i<=k+1;i++) {
        ret += now * muls[k][i] % mod;
        ret %= mod;
        now = now * x % mod;
    }
    return ret;
}

inline void sieve() {
    static int prime[maxn],cnt;
    
    sum[1] = 1;
    for(lli i=2;i<=lim;i++) {
        if( !sum[i] ) {
            prime[++cnt] = i , 
            sum[i] = i - 1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            if( ! ( i % prime[j] ) ) {
                sum[tar] = sum[i] * prime[j];
                break;
            }
            sum[tar] = sum[i] * ( prime[j] - 1 );
        }
    }
    for(int i=1;i<=lim;i++)
        sum[i] += sum[i-1] ,
        sum[i] %= mod;
}

inline lli inisum(lli x) {
    x %= mod;
    return ( x * ( x + 1 ) >> 1 ) % mod;
}
inline lli getsum(lli x) {
    if( x <= lim )
        return sum[x];
    const int t = n / x;
    if( vis[t] )
        return mem[t];
    vis[t] = 1 , mem[t] = inisum(x);
    for(lli i=2,j;i<=x;i=j+1) {
        j = x / ( x / i );
        mem[t] -= ( j - i + 1 ) * getsum( x / i ) % mod;
        mem[t] %= mod;
    }
    return mem[t] = ( mem[t] + mod ) % mod;
}

inline lli calcr(lli x) {
    lli ret = ( getsum(x) << 1 ) % mod - 1;
    return ( ret % mod + mod ) % mod;
}
inline lli getans() {
    lli ret = 0;
    for(lli i=1,j;i<=n;i=j+1) {
        j = n / ( n / i );
        ret += ( ( gk(j) - gk(i-1) ) % mod + mod ) % mod * calcr( n / i ) % mod;
        ret %= mod;
    }
    return ( ret + mod ) % mod;
}

int main() {
    scanf("%lld%d",&n,&k);
    sieve();
    
    printf("%lld\n",getans());
    
    return 0;
}