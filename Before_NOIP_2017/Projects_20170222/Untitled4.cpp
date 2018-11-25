#include<bits/stdc++.h>
using namespace std;
int dis[20][20],dp[20][131072];
int n,m,full;
bool vis[20][131072];
int solve(int x,int sta)
{
    if(vis[x][sta]) return dp[x][sta];
    vis[x][sta]=1;
    for(int i=1;i<=n;i++)
    {
        if((1<<i)&sta)
        {
            dp[x][sta]=min(dp[x][sta],dis[x][i]+solve(i,sta-(1<<i)));
        }
    }
    return dp[x][sta];
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(dis,0x3f,sizeof(dis));
    memset(dp,0x3f,sizeof(dp));
    for(int i=1,a,b,x;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&x);
        dis[a][b]=dis[b][a]=min(dis[a][b],x);
    }
    solve(1,(1<<n)-1);
    printf("%d\n",dp[1][0]);
    return 0;
}

