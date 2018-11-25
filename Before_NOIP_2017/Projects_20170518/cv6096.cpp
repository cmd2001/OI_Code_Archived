#include<bits/stdc++.h>
using namespace std;
const int maxn=1e1+1e2;
int in[maxn][maxn],dx[]={0,1,-1,0,0,1,1,-1,-1},dy[]={0,0,0,1,-1,1,-1,1,-1},n;
long long int dp[maxn][maxn];
bool vis[maxn][maxn],inque[maxn][maxn];
queue<int> xq,yq;
inline void core_bfs(int x,int y)
{
    for(int i=1;i<=8;i++)
    {
        if(x+dx[i]<=n&&x+dx[i]>0&&y+dy[i]<=n&&y+dy[i]>0&&(!in[x+dx[i]][y+dy[i]])&&(!vis[x+dx[i]][y+dy[i]]))
        {
            dp[x+dx[i]][y+dy[i]]+=dp[x][y];
            if(!inque[x+dx[i]][y+dy[i]])
            {
                xq.push(x+dx[i]);
                yq.push(y+dy[i]);
                inque[x+dx[i]][y+dy[i]]=1;
            }
        }
    }
}
inline void bfs()
{
    xq.push(1);yq.push(1);
    vis[1][1]=1,dp[1][1]=1;
    while((!xq.empty())&&(!yq.empty()))
    {
        vis[xq.front()][yq.front()]=1;
        core_bfs(xq.front(),yq.front());
        xq.pop();yq.pop();
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&in[i][j]);
    bfs();
    printf("%lld\n",dp[1][n]);
    /*for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) printf("%lld ",dp[i][j]);
        putchar('\n');
    }*/
    return 0;
}

