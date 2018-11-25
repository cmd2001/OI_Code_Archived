#include<cstdio>
typedef long long int lli;
const int maxn=130;
const int mod=1234567891;

int k,lim;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

lli fac[maxn],rfac[maxn],inv[maxn];

inline void init() {
    *fac = *rfac = inv[1] = 1;
    for(int i=2;i<lim;i++) inv[i] = ( mod - mod / i ) * inv[mod%i] % mod;
    for(int i=1;i<lim;i++) fac[i] = fac[i-1] * inv[i] % mod , rfac[i] = rfac[i-1] * ( mod - inv[i] ) % mod;
}

struct LagrangeInter {
    lli f[maxn];
    lli& operator [] (const int &x) { return f[x]; }
    inline lli calc(lli x) {
        if( x < lim ) return f[x];
        lli ret = 0 , pi = 1;
        for(int i=0;i<lim;i++) pi = pi * ( x - i ) % mod;
        for(int i=0;i<lim;i++) {
            const lli mul = pi * fastpow(x-i,mod-2) % mod , inv = fac[i] * rfac[lim-i-1] % mod;
            ret += f[i] * mul % mod * inv % mod , ret %= mod;
        }
        return ret;
    }
}g,h;

int main() {
    static int T;
    static lli n,a,d;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%lld%lld%lld",&k,&a,&n,&d) , lim = k + 5 , init();
        for(int i=0;i<lim;i++) g[i] = fastpow(i,k);
        for(int i=1;i<lim;i++) g[i] = ( g[i] + g[i-1] ) % mod;
        for(int i=1;i<lim;i++) g[i] = ( g[i] + g[i-1] ) % mod;
        for(int i=0;i<lim;i++) h[i] = g.calc((a+i*d)%mod);
        for(int i=1;i<lim;i++) h[i] = ( h[i] + h[i-1] ) % mod;
        printf("%lld\n",h.calc(n));
    }
    return 0;
}
