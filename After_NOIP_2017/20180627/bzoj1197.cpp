#include<cstdio>
typedef long long int lli;

lli f[17][111];

inline lli g(int n,int m) {
    if( !m ) return 1;
    if( !n ) return 2;
    if( f[n][m] ) return f[n][m];
    return f[n][m] = g(n-1,m-1) + g(n,m-1);
}
int main() {
    static int n,m;
    scanf("%d%d",&m,&n);
    printf("%lld\n",g(n,m));
    return 0;
}
