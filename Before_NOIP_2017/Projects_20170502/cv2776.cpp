#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e2+1e2;
bool g[maxn][maxn],vis[maxn];
int fa[maxn],n,m,ans;


bool dfs(int pos)
{
	for(int i=1;i<=m;i++)
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
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(dfs(i)) ++ans;
	}
}

int main()
{
	freopen("cv.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1,a;i<=n;i++)
	{
		while(scanf("%d",&a)&&a) g[i][a]=1;
	}
	getans();
	printf("%d\n",ans);
}
