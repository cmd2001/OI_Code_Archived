#include<cstdio>
const int maxn=4e6+1e2;
const int mod=1e9+7;

int fac[maxn],inv[maxn];
int n,m,ans;

inline int min(int a,int b) {
    return a < b ? a : b;
}
inline void add(int &a,int b) {
    if( ( a += b ) >= mod ) a -= mod;
}
inline int mul(const int &a,const int &b) {
    return (long long)a*b%mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}
inline int c(int n,int m) {
    return mul(mul(fac[n],inv[m]),inv[n-m]);
}
inline int calc(int n,int m) {
    if( n < 0 ) return 0;
    if( n <= 1 ) return 1;
    n >>= 1;
    return c(n+m,m);
}
inline void pre() {
    const int lim = n + m;
    *fac = 1;
    for(int i=1;i<=lim;i++) fac[i] = mul(fac[i-1],i);
    inv[lim] = fastpow(fac[lim],mod-2);
    for(int i=lim;i;i--) inv[i-1] = mul(inv[i],i);
}
inline void getans() {
    if( n && m ) ans = 1;
    for(int i=2;i<=m;i++) add(ans,calc(n-i,i-1)) , add(ans,calc(n-i-1,i-1));
}

int main() {
    scanf("%d%d",&n,&m) , pre();
    getans() , printf("%d\n",ans);
    return 0;
}
