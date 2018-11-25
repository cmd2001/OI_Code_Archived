#pragma GCC optimize(3)
#include<cstdio>
typedef long long int lli;
const int maxn=4e2+1e1,mod=1e9+7;

lli C[maxn][maxn],pows[maxn*maxn],ans;
int n,m,c;

inline void pre() {
    C[0][0] = 1;
    for(int i=1;i<maxn;i++) {
        C[i][0] = 1;
        for(int j=1;j<=i;j++) C[i][j] = ( C[i-1][j-1] + C[i-1][j] ) % mod;
    }
}
inline int pmo(int x) {
    return x & 1 ? -1 : 1;
}

int main() {
    scanf("%d%d%d",&n,&m,&c) , pre();
    for(int i=0;i<=c;i++) {
        *pows = 1; for(int j=1;j<=n*m;j++) pows[j] = pows[j-1] * ( i + 1 ) % mod;
        for(int j=0;j<=n;j++)
            for(int k=0;k<=m;k++)
                ans += pmo(c-i+n-j+m-k)*C[c][i]%mod*C[n][j]%mod*C[m][k]%mod*pows[j*k]%mod , ans %= mod;
    }
    ans = ( ans % mod + mod ) % mod;
    printf("%lld\n",ans);
    return 0;
}
