#include<cstdio>
#include<algorithm>
#include<cmath>
const int maxn=1e6+1e2;

double f[maxn],mi,ans;

int main() {
    static int p,a,b,c,d,n;
    while( scanf("%d%d%d%d%d%d",&p,&a,&b,&c,&d,&n) == 6 ) {
        for(int i=1;i<=n;i++) f[i] = p * ( std::sin( a * i + b ) + std::cos( c * i + d ) + 2 );
        ans = 0 , mi = f[1];
        for(int i=2;i<=n;i++) ans = std::max( ans , mi - f[i] ) , mi = std::max( mi , f[i] );
        printf("%0.6lf\n",ans);
    }
    return 0;
}