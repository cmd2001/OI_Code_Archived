#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e2+1e1;

char in[maxn][maxn];
int f[maxn][maxn][3],n,m;
bool vis[maxn][maxn][3];
int stx,sty,sts,edx,edy,ans;

queue<int> qx,qy,qs;

inline void init()
{
	memset(in,0,sizeof(in));
	memset(f,0x3f,sizeof(f));
	memset(vis,0,sizeof(vis));
	stx=sty=sts=0;
	edx=edy=0;
	ans=-1;
	while(qx.empty()==0 && qy.empty()==0 && qs.empty()==0)
	{
		qx.pop();
		qy.pop();
		qs.pop();
	}
}

inline void getin()
{
	for(int i=1;i<=n;i++)
	{
		scanf("%s",in[i]+1);
		for(int j=1;j<=m;j++)
		{
			if(in[i][j]=='#') in[i][j]=0;
			else if(in[i][j]=='.') in[i][j]=1;
			else if(in[i][j]=='E') in[i][j]=3;
			else if(in[i][j]=='X') in[i][j]=2;
			else if(in[i][j]=='O') in[i][j]=1,edx=i,edy=j;
		}
	}
}
inline void getst()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(in[i][j]==2)
			{
				//debug<<"i="<<i<<"j="<<j<<endl;
				stx=i,sty=j;
				if(in[i+1][j]==2) sts=2;
				else if(in[i][j+1]==2) sts=1;
				else sts=0;
				return;
			}
		}
}

inline void core_bfs(int x,int y,int s) // s==0 ==> stand ; s==1 ==> right ; s==2 ==> down ;
{
	const int &t=f[x][y][s];
	if(s==0)
	{
		if( x-2>=0 && in[x-1][y] && in[x-2][y] && vis[x-2][y][2]==0 )
		{
			vis[x-2][y][2]=1;
			f[x-2][y][2]=t+1;
			qx.push(x-2);
			qy.push(y);
			qs.push(2);
		}
		if(x+2<=n && in[x+1][y] && in[x+2][y] && vis[x+1][y][2]==0 )
		{
			vis[x+1][y][2]=1;
			f[x+1][y][2]=t+1;
			qx.push(x+1);
			qy.push(y);
			qs.push(2);
		}
		if(y+2<=m && in[x][y+1] && in[x][y+2] && vis[x][y+1][1]==0 )
		{
			vis[x][y+1][1]=1;
			f[x][y+1][1]=t+1;
			qx.push(x);
			qy.push(y+1);
			qs.push(1);
		}
		if(y-2>=0 && in[x][y-1] && in[x][y-2] && vis[x][y-2][1]==0 )
		{
			vis[x][y-2][1]=1;
			f[x][y-2][1]=t+1;
			qx.push(x);
			qy.push(y-2);
			qs.push(1);
		}
	}

	else if(s==1)
	{
		if(x-1>=0 && in[x-1][y] && in[x-1][y+1] && vis[x-1][y][1]==0 )
		{
			vis[x-1][y][1]=1;
			f[x-1][y][1]=t+1;
			qx.push(x-1);
			qy.push(y);
			qs.push(1);
		}
		if(x+1<=n && in[x+1][y] && in[x+1][y+1] && vis[x+1][y][1]==0 )
		{
			vis[x+1][y][1]=1;
			f[x+1][y][1]=t+1;
			qx.push(x+1);
			qy.push(y);
			qs.push(1);
		}
		if(y-1>=0 && in[x][y-1] && in[x][y-1]!=3 && vis[x][y-1][0]==0 )
		{
			vis[x][y-1][0]=1;
			f[x][y-1][0]=t+1;
			qx.push(x);
			qy.push(y-1);
			qs.push(0);
		}
		if(y+2<=m && in[x][y+2] && in[x][y+2]!=3 && vis[x][y+2][0]==0 )
		{
			vis[x][y+2][0]=1;
			f[x][y+2][0]=t+1;
			qx.push(x);
			qy.push(y+2);
			qs.push(0);
		}
	}

	else if(s==2)
	{
		if(x-1>=0 && in[x-1][y] && in[x-1][y]!=3 && vis[x-1][y][0]==0 )
		{
			vis[x-1][y][0]=1;
			f[x-1][y][0]=t+1;
			qx.push(x-1);
			qy.push(y);
			qs.push(0);
		}
		if(x+2<=n && in[x+2][y] && in[x+2][y]!=3 && vis[x+2][y][0]==0 )
		{
			vis[x+2][y][0]=1;
			f[x+2][y][0]=t+1;
			qx.push(x+2);
			qy.push(y);
			qs.push(0);
		}
		if(y-1>=0 && in[x][y-1] && in[x+1][y-1] && vis[x][y-1][2]==0 )
		{
			vis[x][y-1][2]=1;
			f[x][y-1][2]=t+1;
			qx.push(x);
			qy.push(y-1);
			qs.push(2);
		}
		if(y+1<=m && in[x][y+1] && in[x+1][y+1] && vis[x][y+1][2]==0 )
		{
			vis[x][y+1][2]=1;
			f[x][y+1][2]=t+1;
			qx.push(x);
			qy.push(y+1);
			qs.push(2);
		}
	}
}

inline void bfs()
{
	qx.push(stx);
	qy.push(sty);
	qs.push(sts);

	vis[stx][sty][sts]=1;
	f[stx][sty][sts]=0;

	while(qx.empty()==0 && qy.empty()==0 && qs.empty()==0)
	{
		if(qx.front()==edx && qy.front()==edy && qs.front()==0)
		{
			ans=f[edx][edy][0];
			return;
		}
		core_bfs(qx.front(),qy.front(),qs.front());
		qx.pop();qy.pop();qs.pop();
	}

}


int main()
{
	while(scanf("%d%d",&n,&m)==2 && (n||m))
	{
		init();

		getin();
		getst();
		bfs();

		if(ans!=-1) printf("%d\n",ans);
		else puts("Impossible");
	}

	return 0;
}


