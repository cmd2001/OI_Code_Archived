#include<cstdio>
#include<algorithm>
using std::max;
const int maxn=34;
const int inf=0x3f3f3f3f;

int in[maxn][maxn];
bool rev[maxn];
int n,m,fs,ans=-inf;

int main() {
    scanf("%d",&n) , fs = 1 << ( m = ( ( n + 1 ) >> 1 ) );
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",in[i]+j);
    for(int sta=0;sta<fs;sta++) {
        int su = 0;
        for(int i=1;i<=m;i++) {
            rev[i] = ( sta >> ( i - 1 ) ) & 1;
            if( rev[i] ) su -= in[m][i];
            else su += in[m][i];
        }
        for(int i=m+1;i<=n;i++) {
            rev[i] = rev[m] ^ rev[i-m];
            if( rev[i] ) su -= in[m][i];
            else su += in[m][i];
        }
        for(int i=1;i<m;i++) {
            int x = -in[i][m] , y = in[i][m];
            if( rev[m] ) x += in[i+m][m] , y -= in[i+m][m];
            else x -= in[i+m][m] , y += in[i+m][m];
            for(int j=1,p,q;j<m;j++) {
                if( rev[j] ) {
                    p = - in[i][j] + in[i][j+m] + in[i+m][j];
                    q = - in[i][j] - in[i][j+m] + in[i+m][j];
                    if( rev[m] ) p += in[i+m][j+m] , q -= in[i+m][j+m];
                    else p -= in[i+m][j+m] , q += in[i+m][j+m];
                } else {
                    p = - in[i][j] + in[i][j+m] - in[i+m][j];
                    q = - in[i][j] - in[i][j+m] - in[i+m][j];
                    if( rev[m] ) p -= in[i+m][j+m] , q += in[i+m][j+m];
                    else p += in[i+m][j+m] , q -= in[i+m][j+m];
                }
                x += max(p,-p) , y += max(q,-q);
            }
            su += max(x,y);
        }
        ans = max( ans , su );
    }
    printf("%d\n",ans);
    return 0;
}
