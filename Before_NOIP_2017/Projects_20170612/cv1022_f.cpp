#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxm=1e4+1e2;

int in[maxn][maxn],fa[maxm],s[maxm],t[4*maxn],nxt[4*maxm],n,m,k,ans;
bool vis[maxm];
int g[100][100];
inline int convert(int x,int y)
{
	return (x-1)*m+y;
}
inline void addedge(int x1,int y1,int x2,int y2)
{
	g[convert(x1,y1)][convert(x2,y2)]=1;
}

bool dfs(int pos)
{
	for(int i=1;i<=m*n;i++)
	{
		if(g[pos][i]&&(!vis[i]))
		{
			vis[i]=1;
			if((!fa[i])||dfs(fa[i])) {fa[i]=pos;return 1;}
		}
	}
	return 0;
}

void getans()
{
	for(int i=1;i<=n*m;i++)
	{
		memset(vis,0,sizeof(vis));
		if(dfs(i)) ++ans;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,x,y;i<=k;i++)
	{
		scanf("%d%d",&x,&y);
		in[x][y]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) cout<<convert(i,j)<<" ";
		cout<<endl;
	}
		
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
	{
		if(!in[i][j])
		{
			if(i-1>0&&!in[i-1][j]) addedge(i,j,i-1,j);
			if(j-1>0&&!in[i][j-1]) addedge(i,j,i,j-1);
			if(i+1<=n&&!in[i+1][j]) addedge(i,j,i+1,j);
			if(j+1<=m&&!in[i][j+1]) addedge(i,j,i,j+1);
		}
	}
	getans();
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) cout<<fa[convert(i,j)]<<" ";
		cout<<endl;
	}*/
	printf("%d\n",ans);
	return 0;
}
	

