#include<cstdio>
typedef long long int lli;
const int maxn=2e3+1e2;

lli f[maxn][maxn],c[maxn][maxn];
int n,mod;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline int C(int x) {
    return x * ( x - 1 ) >> 1;
}

int main() {
    scanf("%d%d",&n,&mod);
    f[1][1] = 1 , c[0][0] = 1;
    for(int i=1;i<=n;i++) {
        c[i][0] = 1;
        for(int j=1;j<=i;j++) c[i][j] = ( c[i-1][j] + c[i-1][j-1] ) % mod;
    }
    for(int i=2;i<=n;i++) {
        for(int j=1;j<i;j++) f[i][j] = f[j][j] * c[i-1][j-1] % mod * fastpow(2,C(i-j)) % mod;
        f[i][i] = fastpow(2,C(i));
        for(int j=1;j<i;j++) f[i][i] = ( f[i][i] - f[i][j] + mod ) % mod;
    }
    for(int i=1;i<=n;i++) printf("%lld\n",f[n][i]);
    return 0;
}
