#include<cstdio>
typedef long long int lli;
const int maxn=2e6+1e2;
const int mod=20100403;

inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}

int fac[maxn],inv[maxn];

inline int c(int n,int m) {
    return mul(fac[n],mul(inv[m],inv[n-m]));
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    *fac = 1; for(int i=1;i<=n+m;i++) fac[i] = mul(fac[i-1],i);
    inv[n+m] = fastpow(fac[n+m],mod-2); for(int i=n+m;i;i--) inv[i-1] = mul(inv[i],i);
    printf("%d\n",sub(c(n+m,n),c(n+m,n+1)));
    return 0;
}
