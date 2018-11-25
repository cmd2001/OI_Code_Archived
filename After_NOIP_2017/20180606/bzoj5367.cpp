#pragma GCC optimize("O3")
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
typedef long long int lli;
const int maxn=1e2+1e1,maxt=1e3+1e2;
 
lli b[maxn][maxt],s[maxn][maxt];
lli dis[maxn][maxn],mxw[maxn][maxn],f[maxn][maxn];
int n;
 
__inline void floyd1(lli dst[maxn][maxn]) {
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dst[i][j] = std::min( dst[i][j] , dst[i][k] + dst[k][j] );
}
__inline void floyd2(lli dst[maxn][maxn]) {
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dst[i][j] = std::max( dst[i][j] , dst[i][k] + dst[k][j] );
}
__inline bool judge(lli t) {
    memset(f,0xef,sizeof(f));
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
        if( dis[i][j] != 0x3f3f3f3f3f3f3f3fll ) f[i][j] = mxw[i][j] - t * dis[i][j];
        else f[i][j] = 0xefefefefefefefefll;
    }
    floyd2(f);
    for(int i=1;i<=n;i++) if( f[i][i] >= 0 ) return 1;
    return 0;
}
__inline lli bin() {
    lli l = 0 , r = 2e9 + 2 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid) ) l = mid;
        else r = mid;
    }
    return l;
}
 
inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=getchar()) ) if( ch == '-' ) fix = -1;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret * fix;
}
int main() {
    static int m,k;
    n = getint() , m = getint() , k = getint() , memset(dis,0x3f,sizeof(dis));
    for(register int i=1;i<=n;i++) dis[i][i] = 0;
    for(register int i=1;i<=n;i++) for(int j=1;j<=k;j++) b[i][j] = getint() , s[i][j] = getint();
    for(register int i=1,a,b,l;i<=m;i++) a = getint() , b = getint() , l = getint() , dis[a][b] = std::min( dis[a][b] , (lli) l );
    floyd1(dis);
    for(int i=1;i<=n;i++) {
        mxw[i][i] = 0xefefefefefefefefll;
        for(register int j=1;j<=n;j++) if( i != j ) for(register int p=1;p<=k;p++) if( ~s[j][p] && ~b[i][p] ) mxw[i][j] = std::max( mxw[i][j] , s[j][p] - b[i][p] );
    }
    printf("%lld\n",bin());
    return 0;
}
