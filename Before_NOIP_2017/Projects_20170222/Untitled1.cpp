#include<bits/stdc++.h>
using namespace std;
const int maxn=17;
int n,m,t;
int dis[maxn][maxn],dp[maxn][(1<<maxn)+1];
int main()
{
    scanf("%d%d",&n,&m);
    t=1<<(n+1);
    memset(dis,0x3f,sizeof(dis));
    memset(dp,0x3f,sizeof(dp));
    for(int i=1,a,b,x;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&x);
        dis[a][b]=dis[b][a]=min(dis[a][b],x);
    }
    dp[1][1]=0;
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int k=0;k<t;k++)
        {
            if(!(k&(1<<i))) continue;
                for(int j=1;j<=n;j++)
                {
                    if(!(k&(1<<j))) continue;
                    dp[i][k]=min(dp[i][k],dp[j][k-(1<<j)]+dis[i][j]);
                }
        }
    }
    printf("%d\n",dp[1][t-1]);
    return 0;
}
