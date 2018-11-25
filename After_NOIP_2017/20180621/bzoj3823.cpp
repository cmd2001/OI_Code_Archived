#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1e7+1e2;

int fac[maxn],inv[maxn],pows[maxn],n,p;
lli ans;

inline int mul(const int &x,const int &y) {
    return (lli) x * y % p;
}
inline int lucas(int n,int m) {
    if( n < m ) return 0;
    if( n < p && m < p ) return mul(fac[n],mul(inv[m],inv[n-m]));
    return mul(lucas(n/p,m/p),lucas(n%p,m%p));
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}
inline void sieve() {
    const int lim = std::min( n , p - 1 );
    *fac = 1; for(int i=1;i<=lim;i++) fac[i] = mul(fac[i-1],i);
    inv[lim] = fastpow(fac[lim],p-2); for(int i=lim;i;i--) inv[i-1] = mul(inv[i],i);
    *pows = 1; for(int i=1;i<=n;i++) pows[i] = mul(pows[i-1],2);
}


int main() {
    scanf("%d%d",&n,&p) , sieve();
    for(int i=0;i<=n;i++) ans ^= mul(lucas(n,i),pows[n-i]);
    printf("%lld\n",ans);
    return 0;
}
