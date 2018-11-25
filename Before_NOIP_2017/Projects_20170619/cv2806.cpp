#include<bits/stdc++.h>
using namespace std;
const int maxn=25;

int n,m,sx,sy,cnt,dx[]={0,1,-1,0,0},dy[]={0,0,0,1,-1};
bool in[maxn][maxn],vis[maxn][maxn];
queue<int> qx,qy;

inline void core_bfs(int x,int y)
{
	for(int i=1,tx,ty;i<5;i++)
	{
		tx=x+dx[i],ty=y+dy[i];
		if(tx&&tx<=n&&ty&&ty<=m&&in[tx][ty]&&!vis[tx][ty])
		{
			vis[tx][ty]=1;
			cnt++;
			qx.push(tx);
			qy.push(ty);
		}
	}
}

inline void bfs()
{
	cnt=1;
	qx.push(sx);
	qy.push(sy);
	while(!qx.empty()&&!qy.empty())
	{
		core_bfs(qx.front(),qy.front());
		qx.pop();
		qy.pop();
	}
}

int main()
{
	static char s[30];
	while(scanf("%d%d",&m,&n)==2&&m&&n)
	{
		memset(in,0,sizeof(in));
		memset(vis,0,sizeof(vis));
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s+1);
			for(int j=1;j<=m;j++)
			{
				if(s[j]=='.') in[i][j]=1;
				else if(s[j]=='@') sx=i,sy=j;
			}
		}
		bfs();
		printf("%d\n",cnt);
	}
	return 0;
}
		


