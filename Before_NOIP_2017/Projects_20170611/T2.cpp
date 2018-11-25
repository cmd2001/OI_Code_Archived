#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1e3+1e2;

int dx[]={0,1,-1,0,0},dy[]={0,0,0,1,-1};
int in[maxn][maxn],from[maxn][maxn],to[maxn][maxn],ans,sx,sy,tx,ty,m,n;
bool vis[maxn][maxn];

queue<int> qx,qy;

inline void core_bfs(int x,int y,int dst[maxn][maxn])
{
    for(int i=1,tx,ty;i<=4;i++)
    {
        tx=x+dx[i],ty=y+dy[i];
        if(tx>0&&tx<=n&&ty>0&&ty<=m&&in[tx][ty]!=1&&!vis[tx][ty])
        {
            vis[tx][ty]=1;
            dst[tx][ty]=dst[x][y]+1;
            qx.push(tx);
            qy.push(ty);
        }
    }
}

inline void getans()
{
    memset(from,0x3f,sizeof(from));
    memset(to,0x3f,sizeof(to));
    from[sx][sy]=0;
    to[tx][ty]=0;
    qx.push(sx);qy.push(sy);
    while(!qx.empty())
    {
        core_bfs(qx.front(),qy.front(),from);
        qx.pop();
        qy.pop();
    }
    memset(vis,0,sizeof(vis));
    qx.push(tx);qy.push(ty);
    while(!qx.empty())
    {
        core_bfs(qx.front(),qy.front(),to);
        qx.pop();
        qy.pop();
    }
    ans=0x3f3f3f3f;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
    {
        if(in[i][j]==4) ans=min(ans,from[i][j]+to[i][j]);
    }
}

int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    {
        scanf("%d",&in[i][j]);
        if(in[i][j]==2) sx=i,sy=j;
        if(in[i][j]==3) tx=i,ty=j;
    }
    getans();
    printf("%d\n",ans);
}


