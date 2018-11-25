#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=55,maxe=205;
const int mod=1e9+7;

int l[maxn],r[maxn],f[maxe][maxe][maxn],a[maxe][maxe],fac[maxe],inv[maxe];
int n,m,ans;

inline void adde(int &a,const int &b) {
    if( (a += b) >= mod ) a -= mod;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}

inline void pre() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",l+i,r+i) , r[i] = m - r[i] + 1;
    *fac = 1; for(int i=1;i<=m;i++) fac[i] = mul(fac[i-1],i);
    inv[m] = fastpow(fac[m],mod-2); for(int i=m;i;i--) inv[i-1] = mul(inv[i],i);
    for(int i=0;i<=m;i++) for(int j=0;j<=m;j++) a[i][j] = mul(fac[i],inv[i-j]);
}
inline void dp() {
    ***f = 1;
    for(int i=0;i<m;i++) {
        int d = 0 , r = 0 , b = 0;
        for(int j=1;j<=n;j++) d += ( l[j] == i+1 ) , r += ( ::r[j] == i+1 ) , b += ( l[j] < i + 1 && i+1 < ::r[j] );
        for(int j=0;j<=i+1;j++)
            for(int k=0;k<=n-r;k++) {
                if( d && j + 1 >= d ) adde(f[i+1][j+1-d][k+r],mul(mul(d,a[j][d-1]),f[i][j][k]));
                if( j >= d ) {
                    adde(f[i+1][j+1-d][k+r],mul(a[j][d],f[i][j][k]));
                    if( k + r ) adde(f[i+1][j-d][k+r-1],mul(mul(a[j][d],f[i][j][k]),k+r));
                    if(b) adde(f[i+1][j-d][k+r],mul(mul(a[j][d],f[i][j][k]),b));
                }
            }
    }
    for(int i=0;i<=m;i++) adde(ans,f[m][i][0]);
}

int main() {
    pre() , dp() , printf("%d\n",ans);
    return 0;
}
