#include<cstdio>
typedef long long int lli;
const int maxn=1e6+1e2;

lli fac[maxn],inv[maxn];
int mod;

inline lli c(lli n,lli m) {
    return fac[n] * inv[m] % mod * inv[n-m] % mod;
}
inline lli lucas(lli n,lli m) {
    if( n < m ) return 0;
    if( !m ) return 1;
    if( n < mod && m < mod ) return c(n,m);
    return lucas(n/mod,m/mod) * c(n%mod,m%mod) % mod;
}

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

inline void pre() {
    *fac = 1;
    for(int i=1;i<mod;i++) fac[i] = fac[i-1] * i % mod;
    inv[mod-1] = fastpow(fac[mod-1],mod-2);
    for(int i=mod-1;i;i--) inv[i-1] = inv[i] * i % mod;
}

int main() {
    static int T;
    static lli n,m,k,ans;
    scanf("%d",&T);
    while(T--) {
        scanf("%lld%lld%lld%d",&n,&m,&k,&mod) , pre() , ans = 0;
        if( !n && !m ) ans = !k;
        else if( !n ) ans = ( k & 1 ) ? 0 : lucas((k>>1)+m-1,m-1);
        else if( !m ) ans = lucas(k+n-1,n-1);
        else for(lli i=0;i<=k>>1;i++) ans = ( ans + lucas(i+m-1,m-1) * lucas(k-(i<<1)+n-1,n-1) % mod ) % mod;
        printf("%lld\n",ans);
    }
    return 0;
}
