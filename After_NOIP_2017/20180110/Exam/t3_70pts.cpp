#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2,lim=1e6;
const int mod=1e9+7;

lli sum[maxn];
int n,k;

inline lli slowpow(lli base) {
    register lli ret = 1;
    for(register int i=k;i;i--)
        ret = ret * base % mod;
    return ret;
}
inline void pre() {
    static lli pows[maxn];
    static int prime[maxn],mu[maxn],cnt;
    static unsigned char vis[maxn];
    
    mu[1] = 1 , pows[1] = 1;
    for(lli i=2;i<=n;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i,
            mu[i] = -1 , pows[i] = slowpow(i);
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1 , pows[tar] = pows[i] * pows[prime[j]] % mod;
            if( ! ( i % prime[j] ) ) {
                mu[tar] = 0;
                break;
            }
            mu[tar] = -mu[i];
        }
    }
    for(lli i=1;i<=n;i++)
        if( mu[i] ) {
            for(lli j=1;i*j<=n;j++)
                sum[i*j] += mu[i] * pows[j] % mod ,
                sum[i*j] %= mod;
        }
    for(int i=1;i<=n;i++)
        sum[i] = ( ( sum[i] + sum[i-1] ) % mod + mod ) % mod;
}

inline lli getans() {
    lli ret = 0;
    for(lli i=1,j;i<=n;i=j+1) {
        j = n / ( n / i );
        ret += ( sum[j] - sum[i-1] ) * ( n / i ) % mod * ( n / i ) % mod;
        ret %= mod;
    }
    return ( ret + mod ) % mod;
}

int main() {
    scanf("%d%d",&n,&k);
    
    pre();
    
    printf("%lld\n",getans());
    
    return 0;
}