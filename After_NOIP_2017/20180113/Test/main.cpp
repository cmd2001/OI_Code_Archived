#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=110;
const int inf=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

bitset<maxn> used,vis;
char in[maxn][maxn];
int val[maxn][maxn];
int su[maxn],tar[maxn][4];
int n,m,cnt,pcn,ans=inf;

int main() {
    srand(time(0));
    scanf("%d%d%*d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",in[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] == 'o' )
                val[i][j] = ++cnt;
    debug<<"explained"<<endl;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++)
            debug<<val[i][j];
        debug<<endl;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] == 'l' ) {
                ++pcn;
                for(int k=0;k<4;k++) {
                    const int tx = i + dx[k] , ty = j + dy[k];
                    if( val[tx][ty] ) {
                        debug<<"pcn = "<<pcn<<"tx = "<<tx<<"ty = "<<ty<<endl;
                        tar[pcn][su[pcn]++] = val[tx][ty];
                    }
                }
                if( !su[pcn] )
                    --pcn;
            }
    for(int i=1;i<=pcn;i++) debug<<su[i]<<" ";debug<<endl;
    for(int i=1;i<=1000000;i++) {
        vis &= 0 , used &= 0;
        for(int j=1;j<=pcn;j++) {
            int t = rand() % su[j];
            if( !vis[tar[j][t]] ) vis[tar[j][t]] = 1 , used[j] = 1;
        }
        for(int j=1;j<=pcn;j++)
            if( !used[j] ) {
                for(int k=0;k<su[j];k++)
                    if( !vis[tar[j][k]] ) {
                        vis[tar[j][k]] = 1;
                        break;
                    }
            }
        ans = min( ans , (signed)vis.count() );
    }
    
    printf("%d\n",ans);
    
    return 0;
}