#include<cstdio>
typedef long long int lli;
const int maxn=1e6+1e2,mod=65536;

lli f[maxn][2],sf[maxn][2];

int main() {
    static int n,m;
    scanf("%d%d",&n,&m) , sf[0][0] = sf[0][1] = 1;
    for(int i=1;i<=n;i++) {
        /*for(int j=1;j<m&&j<=i;j++) f[i][1] = ( f[i][1] + f[i-j][0] ) % mod;
        for(int j=1;j<=i;j++) f[i][0] = ( f[i][0] + f[i-j][1] ) % mod;*/
        f[i][1] = ( sf[i-1][0] - ( i >= m ? sf[i-m][0] : 0 ) + mod ) % mod , f[i][0] = sf[i-1][1] ,
        sf[i][1] = ( sf[i-1][1] + f[i][1] ) % mod , sf[i][0] = ( sf[i-1][0] + f[i][0] ) % mod;
    }
    printf("%lld\n",(f[n][0]+f[n][1])%mod);
    return 0;
}
