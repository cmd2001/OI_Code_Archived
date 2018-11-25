#include<cstdio>
#define lli long long int

lli n,k,mod,ans;

inline lli fastpow(lli base,lli tim,lli mod) {
    lli now = base % mod , ret = 1;
    while( tim ) {
        if ( tim & 1 ) ret = ret * now % mod;
        if( tim >>= 1 ) now = now * now % mod;
    }
    return ret % mod;
}
inline lli c(lli n,lli m) {
    lli inv = 1 , ret = 1;
    for(lli i=n;i>n-m;i--) ret = ret * i % mod;
    for(lli i=1;i<=m;i++) inv = inv * i % mod;
    return ret * fastpow(inv,mod-2,mod) % mod;
}

int main() {
    scanf("%lld%lld%lld",&n,&k,&mod);
    ans = c(n-1,k-1) * fastpow(n-k,k-1,mod) % mod * fastpow(k,n-k-1,mod) % mod;
    printf("%lld\n",ans);
    return 0;
}
