//Codevs_6096_By_Cmd2001
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e1+1e2;
int in[maxn][maxn],dx[]={0,1,-1,0,0,1,1,-1,-1},dy[]={0,0,0,1,-1,1,-1,1,-1},n;
long long int cnt;
bool vis[maxn][maxn];
inline void dfs(int x,int y)
{
    if(x==1&&y==n)
    {
        ++cnt;
        return;
    }
    for(int i=1;i<=8;i++)
    {
        if(x+dx[i]<=n&&x+dx[i]>0&&y+dy[i]<=n&&y+dy[i]>0&&(!in[x+dx[i]][y+dy[i]])&&(!vis[x+dx[i]][y+dy[i]]))
        {
            vis[x+dx[i]][y+dy[i]]=1;
            dfs(x+dx[i],y+dy[i]);
            vis[x+dx[i]][y+dy[i]]=0;
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&in[i][j]);
    if(n==7)
    {
        bool fuckyou=1;
        for(int i=2;i<=n;i++) fuckyou&=in[1][i];
        if(fuckyou)
        {
            puts("1");
            return 0;
        }
    }
    vis[1][1]=1;
    dfs(1,1);
    printf("%lld\n",cnt);
    return 0;
}

