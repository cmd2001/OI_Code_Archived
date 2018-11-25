#include<cstdio>
#include<cstring>
#include<algorithm>
#include<functional>
const int maxn=51,maxk=21;
const int minf=0xefefefef;

int in[maxn][maxn],srt[maxn],len;
int f[maxn][maxn][maxk][maxk]; // f[pos_x][pos_y][given][used]

inline void up(int &dst,const int &x) {
    dst = dst < x ? x : dst;
}

int main() {
    static int T,n,m,k,ans;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d",&n,&m,&k) , memset(f,0xef,sizeof(f)) , ans = ****f;
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",in[i]+j);
        f[1][1][0][0] = in[1][1] , f[1][1][1][0] = 0;
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
            for(int g=0;g<=k;g++) for(int u=0;u<=k;u++) if( f[i][j][g][u] != minf && j != m ) {
                    if( g < k ) up(f[i][j+1][g+1][u],f[i][j][g][u]);
                    up(f[i][j+1][g][u],f[i][j][g][u]+in[i][j+1]);
            }
            if( i != n ) {
                len = 0;
                for(int t=1;t<j;t++) srt[++len] = in[i+1][t];
                for(int t=j+1;t<=m;t++) srt[++len] = in[i][t];
                std::sort(srt+1,srt+1+len,std::greater<int>());
                for(int i=1;i<=len;i++) srt[i] += srt[i-1];
                for(int g=0;g<=k;g++) for(int u=0;u<=k;u++) if( f[i][j][g][u] != minf ) for(int sel=0;sel+u<=k;sel++) {
                    if( g + 1 <= k ) up(f[i+1][j][g+1][u+sel],f[i][j][g][u]+srt[sel]);
                    up(f[i+1][j][g][u+sel],f[i][j][g][u]+in[i+1][j]+srt[sel]);
                }
            }
        }
        for(int i=0;i<=k;i++) up(ans,f[n][m][i][i]);
        printf("%d\n",ans);
    }
    return 0;
}
