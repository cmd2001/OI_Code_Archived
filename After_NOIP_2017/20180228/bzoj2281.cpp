#include<cstdio>
#define lli long long int
const int maxb=16,maxk=2e2+5e0,maxn=2e4+1e2;
const int mod = 1e9 + 7;

lli cc[maxn][maxk];
lli f[maxb][maxn],pows[maxb],ans;

inline lli c(int n,int m) {
    m = m < n - m ? m : n - m;
    return cc[n][m];
}
int main() {
    static int n,m,d;
    scanf("%d%d%d",&n,&m,&d);
    *pows = 1;
    for(int i=1;i<maxb;i++) pows[i] = pows[i-1] << 1;
    cc[0][0] = 1;
    for(int i=0;i<=n;i++) {
        *cc[i] = 1;
        for(int j=1;j<=m&&j<=i;j++) cc[i][j] = ( cc[i-1][j] + cc[i-1][j-1] ) % mod;
    }
    f[0][0] = 1;
    for(int i=0;i<15;i++)
        for(int j=0;j<=n-m;j++)
            for(int k=0;k*(d+1)<=m/2;k++) {
                const int tar = j + k * ( d + 1 ) * pows[i];
                if( tar > n - m ) break;
                f[i+1][tar] += f[i][j] * c(m/2,k*(d+1)) % mod , f[i+1][tar] %= mod;
            }
    for(int i=0;i<=n-m;i++) ans += f[15][i] * c(n-m/2-i,m/2) % mod , ans %= mod;
    ans = ( c(n,m) - ans + mod ) % mod;
    printf("%lld\n",ans);
    return 0;
}
