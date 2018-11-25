#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=21;

int n,maxd;
double dp[1048576][maxn],dis[maxn][maxn],in[maxn][3],ans; // first is visted,last is now at;
bool vis[maxn];

inline int zip()
{
    int ret=0;
    for(int i=1;i<=n;i++) ret|=(vis[i]<<(i-1));
    return ret;
}
inline void unzip(int x)
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) vis[i]=(x>>(i-1))&1;
}

double getdis(int x,int y)
{
    double dx=in[x][1]-in[y][1],dy=in[x][2]-in[y][2];
    return sqrt(dx*dx+dy*dy);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&in[i][1],&in[i][2]);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j]=getdis(i,j);

    memset(dp,0x42,sizeof(dp));
    for(int i=1;i<=n;i++) dp[0][i]=0;
    maxd=1<<n;
    for(int i=0;i<maxd;i++)
    {

        for(int j=1;j<=n;j++)
        {
            //debug<<"i="<<i<<"j="<<j<<endl;
            //debug<<dp[i][j]<<endl;
            unzip(i);
            for(int k=1;k<=n;k++)
            {
                if(!vis[k])
                {
                    vis[k]=1;
                    dp[zip()][k]=min(dp[zip()][k],dp[i][j]+dis[j][k]);
                    vis[k]=0;
                }
            }
        }
    }
    ans=dp[maxd-1][1];
    for(int i=1;i<=n;i++) ans=min(ans,dp[maxd-1][i]);
    printf("%.2f\n",ans);
    return 0;
}



