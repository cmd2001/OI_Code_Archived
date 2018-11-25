#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e2+1e1,maxt=1e3+1e2;

lli b[maxn][maxt],s[maxn][maxt];
lli dis[maxn][maxn],mxw[maxn][maxn],f[maxn][maxn];
int n;

inline void floyd1(lli dst[maxn][maxn]) {
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dst[i][j] = std::min( dst[i][j] , dst[i][k] + dst[k][j] );
}
inline void floyd2(lli dst[maxn][maxn]) {
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dst[i][j] = std::max( dst[i][j] , dst[i][k] + dst[k][j] );
}
inline bool judge(int t) {
    memset(f,0xef,sizeof(f));
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j] = mxw[i][j] - t * dis[i][j];
    /*debug<<"inital f = "<<endl;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) debug<<f[i][j]<<" "; debug<<endl;
    }*/
    floyd2(f);
    for(int i=1;i<=n;i++) if( f[i][i] >= 0 ) return 1;
    return 0;
}
inline int bin() {
    int l = 0 , r = 1e9 + 2 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid) ) l = mid;
        else r = mid;
    }
    return l;
}

int main() {
    static int m,k;
    scanf("%d%d%d",&n,&m,&k) , memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++) dis[i][i] = 0;
    for(int i=1;i<=n;i++) for(int j=1;j<=k;j++) scanf("%lld%lld",b[i]+j,s[i]+j);
    for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , dis[a][b] = std::min( dis[a][b] , (lli) l );
    floyd1(dis);
    /*for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) debug<<dis[i][j]<<" "; debug<<endl;
    }*/
    for(int i=1;i<=n;i++) {
        mxw[i][i] = 0xefefefefefefefefll;
        for(int j=1;j<=n;j++) if( i != j ) for(int p=1;p<=k;p++) if( ~s[j][p] && ~b[i][p] ) mxw[i][j] = std::max( mxw[i][j] , s[j][p] - b[i][p] );
    }
    /*for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) debug<<mxw[i][j]<<" "; debug<<endl;
    }*/
    printf("%d\n",bin());
    return 0;
}
