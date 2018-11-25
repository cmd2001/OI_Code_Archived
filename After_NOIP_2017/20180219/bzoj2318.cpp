#include<cstdio>
const int maxn=1e3+1e2;

double f[maxn],g[maxn],p,q;
int n; 

inline void getans() {
    *f = 0 , *g = 1;
    for(int i=1;i<=n;i++) {
        if( f[i-1] > g[i-1] ) p = 1 - p , q = 1 - q;
        f[i] = ( p * g[i-1] + ( 1 - p ) * q * f[i-1] ) / ( 1 - ( 1 - p ) * ( 1 - q ) );
        g[i] = ( q * f[i-1] + ( 1 - q ) * p * g[i-1] ) / ( 1 - ( 1 - p ) * ( 1 - q ) );
        if( f[i-1] > g[i-1] ) p = 1 - p , q = 1 - q;
    }
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%lf%lf",&n,&p,&q) , n = n > 1000 ? 1000 : n;
        getans();
        printf("%0.6lf\n",f[n]);
    }
    return 0;
}
