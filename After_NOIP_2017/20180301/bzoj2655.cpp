#include<cstdio>
#define lli long long int
const int maxn=5e2+1e1;

lli inv[maxn],fac[maxn],fac_inv[maxn],pows[maxn],b[maxn],g[maxn],f[maxn];
lli A,n,mod;

inline lli c(int n,int m) {
    return fac[n] * fac_inv[m] % mod * fac_inv[n-m] % mod;
}
inline lli mo(int t) {
    return t & 1 ? -1ll : 1ll;
}
inline void pre() {
    *inv = *fac = *fac_inv = *pows = 1;
    inv[1] = fac[1] = fac_inv[1] = 1 , pows[1] = A + 1;
    for(int i=2;i<=n+1;i++)
        inv[i] = ( mod - mod / i ) * inv[mod%i] % mod ,
        fac[i] = fac[i-1] * i % mod ,
        fac_inv[i] = fac_inv[i-1] * inv[i] % mod ,
        pows[i] = pows[i-1] * ( A + 1 ) % mod;
    *b = 1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<i;j++)
            b[i] = ( b[i] + c(i+1,j) * b[j] % mod ) % mod;
        b[i] = b[i] * inv[i+1] % mod;
        b[i] = mod - b[i];
    }
    for(int k=0;k<=n;k++) {
        for(int i=1;i<=k+1;i++)
            g[k] = ( g[k] + c(k+1,i) * b[k+1-i] % mod * pows[i] % mod ) % mod;
        g[k] = g[k] * inv[k+1] % mod;
    }
}
inline void dp() {
    *f = 1;
    for(int i=1;i<=n;i++) {
        f[i] = g[1] * f[i-1] % mod;
        for(int j=0;j<=i-2;j++)
            f[i] = ( f[i] + mo(i-j+1) * f[j] * c(i-1,i-1-j) % mod * fac[i-j-1] % mod * g[i-j] % mod ) % mod;
        f[i] = ( f[i] + mod ) % mod;
    }
}

int main() {
    scanf("%lld%lld%lld",&A,&n,&mod) , pre();
    dp() , printf("%lld\n",f[n]);
    return 0;
}
