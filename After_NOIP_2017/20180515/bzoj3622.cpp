#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=2e3+1e2;
const int mod=1e9+9;

lli f[2][maxn],g[maxn],fac[maxn],inv[maxn];
int a[maxn],b[maxn],nxt[maxn];
int n,k;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline lli c(int n,int m) {
    return fac[n] * inv[m] % mod * inv[n-m] % mod;
}
inline void pre() {
    *fac = 1;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i % mod;
    inv[n] = fastpow(fac[n],mod-2);
    for(int i=n;i;i--) inv[i-1] = inv[i] * i % mod;
    std::sort(a+1,a+1+n) , std::sort(b+1,b+1+n);
    for(int i=1,j=1;i<=n;i++) {
        while( j <= n && b[j] <= a[i] ) j++;
        nxt[i] = j - 1;
    }
}
inline void dp() {
    int cur = 0;
    f[cur][0] = 1;
    for(int i=1;i<=n;i++) {
        cur ^= 1 , f[cur][0] = 1;
        for(int j=1;j<=i;j++) f[cur][j] = ( f[cur^1][j] + f[cur^1][j-1] * std::max( nxt[i] - ( j - 1 ) , 0 ) % mod ) % mod;
    }
    for(int i=n;i;i--) {
        g[i] = f[cur][i] * fac[n-i] % mod;
        for(int j=i+1;j<=n;j++) g[i] = ( g[i] - g[j] * c(j,i) % mod + mod ) % mod;
    }
}

int main() {
    scanf("%d%d",&n,&k) , k = ( n + k ) >> 1;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    pre() , dp() , printf("%lld\n",g[k]);
    return 0;
}
