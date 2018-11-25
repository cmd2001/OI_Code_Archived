#include<cstdio>
typedef long long int lli;
const int maxn=1e7+1e2;
const int mod=1e9+7;

int miv[maxn],fac[maxn],inv[maxn],f[maxn];
int l,r,ans,n,siz,su;

inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}
inline void adde(int &a,const int &b) {
    if( ( a += b ) >= mod ) a -= mod;
}
inline void sube(int &a,const int &b) {
    if( ( a -= b ) < 0 ) a += b;
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}
inline int p(int n,int m) {
    return mul(fac[n],inv[n-m]);
}
inline int c(int n,int m) {
    return mul(p(n,m),inv[m]);
}

inline void sieve() {
    static int prime[maxn/10],cnt;
    static char vis[maxn];
    miv[1] = maxn;
    for(int i=2;i<=r;i++) {
        if( !vis[i] ) miv[i] = prime[++cnt] = i;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=r;j++) {
            vis[i*prime[j]] = 1 , miv[i*prime[j]] = prime[j];
            if( ! ( i % prime[j] ) ) break;
        }
    }
}

inline void pre() {
    *fac = 1; for(int i=1;i<=r;i++) fac[i] = mul(fac[i-1],i);
    inv[r] = fastpow(fac[r],mod-2); for(int i=r;i;i--) inv[i-1] = mul(inv[i],i);
}

inline void getans() {
    for(int i=l;i<=r;i++) if( i / miv[i] < l ) ++siz;
    n = r - l + 1;
    for(int i=siz;i<=n;i++) f[i] = mul(c(i-1,siz-1),fac[siz]);
    for(int i=siz;i<=n;i++) adde(ans,mul(f[i],i));
    ans = mul(ans,fac[n-siz]);
}

int main() {
    scanf("%d%d",&l,&r);
    sieve() , pre() , getans();
    printf("%lld\n",ans);
    return 0;
}
