#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+1e2,maxb=1<<8,maxt=16;
const int inf=0x3f3f3f3f;

int in[maxn],b[maxn];
int f[maxn][maxb][maxt];

inline int calcval(int fm,int to) {
    if( !fm ) return 0;
    return in[fm] ^ in[to];
}
inline bool legal(int i,int sta) {
    for(int l=0;l<8;l++) if( ! ( sta & ( 1 << l ) ) )
    for(int t=0;t<8;t++) if( ( sta & ( 1 << t ) ) && t > l + b[i+l] ) return 0;
    return 1;
}
inline void trans(int i,int j,int k) {
    for(int b=0;b<8;b++)
        if( ! ( j & ( 1 << b ) ) )
            f[i][j|(1<<b)][b] = min( f[i][j|(1<<b)][b] , f[i][j][k] + calcval(i+k,i+b) );
}
inline void transall(int i,int lim) {
    const int full = 1 << 8;
    for(int j=0;j<full;j++) {
        if( !legal(i,j) ) continue;
        for(int k=-8;k<8;k++) {
            trans(i,j,k);
            if( k != -8 && ( j & 1 ) ) f[i+1][j>>1][k-1] = min( f[i+1][j>>1][k-1] , f[i][j][k] );
        }
    }
}

int main() {
    static int T,n,ans;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n) , memset(f,0x3f,sizeof(f)) , f[1][0][-1] = 0 , ans = inf;
        for(int i=1;i<=n;i++) scanf("%d%d",in+i,b+i);
        for(int i=1;i<=n;i++) transall(i,b[i]);
        for(int i=-8;i<=0;i++) ans = min( ans , f[n][1][i] );
        printf("%d\n",ans);
    }
    return 0;
}
