#include<cstdio>
#include<cstring>
const int maxn=3e2+1e1;

long double f[maxn][maxn],pows[maxn][maxn],p[maxn],d[maxn],ans;
int n,r;

inline void calc() {
    memset(f,0,sizeof(f)) , memset(pows,0,sizeof(pows)) , ans = 0 , f[0][r] = 1.0;
    for(int i=1;i<=n;i++) pows[i][0] = 1.0;
    for(int i=1;i<=r;i++) pows[0][i] = 1.0;
    for(int i=1;i<=n;i++) for(int j=1;j<=r;j++) pows[i][j] = pows[i][j-1] * ( 1.0 - p[i] );
    for(int i=1;i<=n;i++) for(int j=1;j<=r;j++) f[i][j] = f[i-1][j] * pows[i-1][j] + f[i-1][j+1] * ( 1.0 - pows[i-1][j+1] );
    for(int i=1;i<=n;i++) for(int j=1;j<=r;j++) ans += f[i][j] * ( 1.0 - pows[i][j] ) * d[i];
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&r);
        for(int i=1;i<=n;i++) scanf("%Lf%LF",p+i,d+i);
        calc() , printf("%0.10Lf\n",ans);
    }
    return 0;
}
