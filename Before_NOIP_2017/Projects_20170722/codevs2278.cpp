#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+1e2;

bool vis[2][maxn];
int n,cur,st,mx,in,ans=-1;

int main()
{
	scanf("%d%d%d",&n,&st,&mx);
	vis[cur][st]=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&in);
		cur^=1;
		memset(vis[cur],0,sizeof(vis[1]));
		for(int k=0;k<=mx;k++)
		{
			if(k+in<=mx&&vis[cur^1][k+in]) vis[cur][k]=1;
			if(k-in>=0&&vis[cur^1][k-in]) vis[cur][k]=1;
		}
	}
	
	for(int i=0;i<=mx;i++) if(vis[cur][i]) ans=max(ans,i);
	
	printf("%d\n",ans);
	
	return 0;
}
