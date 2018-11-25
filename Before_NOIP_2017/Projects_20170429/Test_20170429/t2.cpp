//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+1e1;
short int in[maxn][maxn],qx[maxn*maxn],qy[maxn*maxn],s,e,dx[]={0,1,-1,0,0},dy[]={0,0,0,1,-1};
int to[maxn][maxn],back[maxn][maxn],m,n;
bool vis[maxn][maxn];
short int sx,sy,tx,ty,tmp;
int ans=0x3f3f3f3f;

void bfs1(int x,int y)
{
    //debug<<"x="<<x<<"y="<<y<<endl;
    for(int i=1;i<=4;i++)
    {
        if(x+dx[i]>0&&x+dx[i]<=n&&y+dy[i]>0&&y+dy[i]<=m)
        if(vis[x+dx[i]][y+dy[i]]==0&&in[x+dx[i]][y+dy[i]]!=1&&in[x+dx[i]][y+dy[i]]!=3)
        {
            vis[x+dx[i]][y+dy[i]]=1;
            to[x+dx[i]][y+dy[i]]=to[x][y]+1;
            qx[++e]=x+dx[i],qy[e]=y+dy[i];
        }
    }
}

void bfs2(int x,int y)
{
    for(int i=1;i<=4;i++)
    {
        if(x+dx[i]>0&&x+dx[i]<=n&&y+dy[i]>0&&y+dy[i]<=m)
        if(vis[x+dx[i]][y+dy[i]]==0&&in[x+dx[i]][y+dy[i]]!=1)
        {
            vis[x+dx[i]][y+dy[i]]=1;
            back[x+dx[i]][y+dy[i]]=back[x][y]+1;
            qx[++e]=x+dx[i],qy[e]=y+dy[i];
        }
    }
}
int main()
{
    memset(to,0x3f,sizeof(to));memset(back,0x3f,sizeof(back));
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    {
        scanf("%d",&in[i][j]);
        if(in[i][j]==2) sx=i,sy=j;
        if(in[i][j]==3) tx=i,ty=j;
    }
    qx[s=e=1]=sx,qy[s=e=1]=sy;
    vis[sx][sy]=1;
    to[sx][sy]=0;
    while(s<=e)
    {
        bfs1(qx[s++],qy[s]);
    }
    memset(vis,0,sizeof(vis));
    memset(qx,0,sizeof(qx));
    memset(qy,0,sizeof(qy));
    qx[s=e=1]=tx,qy[s=e=1]=ty;
    vis[tx][ty]=1;
    back[tx][ty]=0;
    while(s<=e)
    {
        bfs2(qx[s++],qy[s]);
    }
    /*for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++) debug<<back[i][j]<<"    ";
        debug<<endl;
    }*/
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(in[i][j]==4) ans=min(ans,to[i][j]+back[i][j]);
    printf("%d\n",ans);
    return 0;
}
