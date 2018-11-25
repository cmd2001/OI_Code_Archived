#include<cstdio>
typedef long long int lli;
const int maxn=3e3+1e2;

int n,m,mod;

inline lli c(lli x) {
    return x * ( x - 1 ) % mod;
}

lli f[maxn][maxn];

int main() {
    scanf("%d%d%d",&n,&m,&mod);
    f[0][0] = 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            f[i][j] = ( i - 1 ) * f[i-1][j] % mod;
            if( i >= 3 ) f[i][j] = ( f[i][j] + f[i-3][j-1] * c(i-1) % mod ) % mod;
        }
    printf("%lld\n",f[n][m]);
    return 0;
}