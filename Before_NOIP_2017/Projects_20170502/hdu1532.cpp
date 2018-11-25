#include<bits/stdc++.h>
using namespace std;
const int maxn=310,inf=0x3f3f3f3f;
int v[maxn][maxn],m,n,f,t;
bool vis[maxn];

int dfs(int from,int flow)
{
	if(from==t) return flow;
	int ret=0,tmp;
	for(int i=1;i<=n;i++)
	{
		if(v[from][i]&&!vis[i])
		{
			vis[i]=1;
			tmp=dfs(i,min(v[from][i],flow));
			v[from][i]-=tmp;
			v[i][from]+=tmp;
			ret+=tmp;
		}
	}
	return min(ret,flow);
}
int getans()
{
	int ret=0,tmp;
	while(1)
	{
		memset(vis,0,sizeof(vis));
		tmp=dfs(f,inf);
		if(tmp==0) return ret;
		ret+=tmp;
	}
}

int main()
{
	while(scanf("%d%d",&m,&n)==2&&m&&n)
	{
		memset(v,0,sizeof(v));
		f=1,t=n;
		for(int i=1,a,b,x;i<=m;i++)
		{
			scanf("%d%d%d",&a,&b,&x);
			v[a][b]+=x;
		}
		printf("%d\n",getans());
	}
	return 0;
}
