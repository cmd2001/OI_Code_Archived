#include<cstdio>
typedef long long int lli;
const int maxn=1e6+1e2;
const int mod=1e9+7;

char in[maxn];
int b[maxn],w[maxn];
lli f[maxn][2][3];

int main() {
    static int n,k;
    scanf("%d%d",&n,&k);
    scanf("%s",in+1) , in[++n] = 'X';
    for(int i=1;i<=n;i++)
        b[i] = b[i-1] + ( in[i] == 'B' ) ,
        w[i] = w[i-1] + ( in[i] == 'W' ) ;
    f[0][1][0] = 1;
    for(int i=1;i<=n;i++) {
        if( in[i] != 'W' ) for(int j=0;j<3;j++) f[i][0][j] = ( f[i-1][0][j] + f[i-1][1][j] ) % mod;
        if( in[i] != 'B' ) for(int j=0;j<3;j++) f[i][1][j] = ( f[i-1][0][j] + f[i-1][1][j] ) % mod;
        if( i >= k ) {
            if( in[i] != 'W' && w[i] == w[i-k] ) {
                f[i][0][1] = ( f[i][0][1] + f[i-k][1][0] ) % mod ,
                f[i][0][0] = ( f[i][0][0] - f[i-k][1][0] + mod ) % mod ;
            }
            if( in[i] != 'B' && b[i] == b[i-k] ) {
                f[i][1][2] = ( f[i][1][2] + f[i-k][0][1] ) % mod ,
                f[i][1][1] = ( f[i][1][1] - f[i-k][0][1] + mod ) % mod;
            }
        }
    }
    printf("%lld\n",f[n][0][2]);
    return 0;
}
