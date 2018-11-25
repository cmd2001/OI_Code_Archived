#include<cstdio>
#define lli long long int
const int maxn=65,maxe=maxn*maxn;

lli fac[maxn],inv[maxn],g[maxn][maxn],pows[maxe],ans;
int ss[maxn],cnt;
int n,m,mod;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret % mod;
}
inline lli gcd(lli a,lli b) {
    register lli t;
    while( t = a % b )
        a = b , b = t;
    return b;
}

inline void dfs(int sum,int last) {
    if( sum == n ) {
        lli t = 0 , add = 1; // fac[n] * inv[n] == 1 .
        for(int i=1;i<=cnt;i++) // Points will be ordered if you decides first point .
            add = add * inv[ss[i]] % mod ,
            add = add * fac[ss[i]-1] % mod ;
        for(int l=1,r;l<=cnt;l=r+1) {
            for(r=l;r<cnt&&ss[r+1]==ss[l];r++) ;
            add = add * inv[r-l+1] % mod;
        }
        for(int i=1;i<=cnt;i++) {
            t += ( ss[i] >> 1 );
            for(int j=i+1;j<=cnt;j++)
                t += g[ss[i]][ss[j]];
        }
        add = add * pows[t] % mod;
        ans += add , ans %= mod;
    } else {
        for(int i=last;sum+i<=n;i++) {
            ss[++cnt] = i;
            dfs(sum+i,i);
            ss[cnt--] = 0;
        }
    }
}

inline void pre() {
    *fac = 1;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i % mod;
    inv[n] = fastpow(fac[n],mod-2);
    for(int i=n-1;~i;i--) inv[i] = inv[i+1] * ( i + 1 ) % mod;
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) g[i][j] = g[j][i] = gcd(i,j);
    *pows = 1;
    for(int i=1;i<=n*n;i++) pows[i] = pows[i-1] * m % mod;
}

int main() {
    scanf("%d",&n), m = 2 , mod = 997 , pre();
    dfs(0,1);
    printf("%lld\n",ans); 
    return 0;
}

