#include<cstdio>
typedef long long int lli;
const int maxn=2e3+1e2;

lli c[maxn][maxn],fac[maxn],ans;
int n,mod;

int main() {
    scanf("%d%d",&n,&mod);
    c[0][0] = 1 % mod;
    for(int i=1;i<=n;i++) {
        c[i][0] = 1 % mod;
        for(int j=1;j<=i;j++) c[i][j] = ( c[i-1][j-1] + c[i-1][j] ) % mod;
    }
    *fac = 1 % mod;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i % mod;
    for(int i=2;i<=n;i++) for(int siz=1;siz<=n-i+1;siz++) {
        ans += siz * ( n - siz ) % mod * c[n-i][siz-1] % mod *fac[siz] % mod * i % mod * (i-1) % mod * fac[n-siz-1] % mod;
        ans %= mod;
    }
    printf("%lld\n",ans);
    return 0;
}