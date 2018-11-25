#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
typedef long long int lli;
using namespace std;
const int maxn=33;
const lli inf = 0x3f3f3f3f3f3f3f3fll; // inf may overflow if it isn't lli_inf .

lli f[maxn][maxn][maxn][maxn][2];
int n,m,t,len;

inline void update(lli &dst,const lli &x) {
    dst = min( dst , x );
}
inline int getlength(int x) {
    return (int)(log2(x)+1);
}

int main() {
    scanf("%d%d%d",&n,&m,&t) , memset(f,0x3f,sizeof(f)) , *****f = 0;
    len = max( getlength(t) , max( getlength(n) , getlength(m) ) );
    n = __builtin_popcount(n) , m = __builtin_popcount(m) , t = __builtin_popcount(t);
    for(int l=0;l<=len;l++) for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) for(int k=0;k<=t;k++) {
        if( f[l][i][j][k][0] != inf ) {
            update(f[l+1][i+1][j+1][k+1][1],f[l][i][j][k][0]+(1ll<<(l+1)));
            update(f[l+1][i+1][j][k+1][0],f[l][i][j][k][0]+(1ll<<l));
            update(f[l+1][i][j+1][k+1][0],f[l][i][j][k][0]+(1ll<<l));
            update(f[l+1][i][j][k][0],f[l][i][j][k][0]);
        }
        if( f[l][i][j][k][1] != inf ) {
            update(f[l+1][i+1][j+1][k+1][1],f[l][i][j][k][1]+(1ll<<(l+1)));
            update(f[l+1][i+1][j][k][1],f[l][i][j][k][1]+(1ll<<l));
            update(f[l+1][i][j+1][k][1],f[l][i][j][k][1]+(1ll<<l));
            update(f[l+1][i][j][k][0],f[l][i][j][k][1]);
        }
    }
    const lli& ans = f[len][n][m][t][0];
    if( ans == inf ) puts("-1");
    else printf("%lld\n",ans);
    return 0;
}
