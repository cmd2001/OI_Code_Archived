#include<cstdio>
#include<algorithm>
const int maxn=5e3+1e2;

int f[maxn],g[maxn],in[maxn][maxn];

int main() {
    static int n,h,d;
    scanf("%d%d%d",&n,&h,&d);
    for(int i=1,t,x;i<=n;i++) {
        scanf("%d",&t);
        while(t--) scanf("%d",&x) , ++in[i][x];
    }
    for(int i=h,t;i;i--) {
        t = ( i + d <= h ) ? f[i+d] : 0 ;
        for(int j=1;j<=n;j++)
            g[j] = std::max( g[j] , t ) + in[j][i] ,
            f[i] = std::max( f[i] , g[j] );
    }
    printf("%d\n",f[1]);
    return 0;
}
