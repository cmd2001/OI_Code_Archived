#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxm=1e5+1e2,maxn=1e2+1e1;

int in[maxn],cnt[maxn],used[maxm],n,m,ans;
bool vis[maxm];

int main()
{
	while(scanf("%d%d",&n,&m)==2&&(n||m))
	{
		memset(vis,0,sizeof(vis));
		vis[0]=1;
		ans=0;
		for(int i=1;i<=n;i++) scanf("%d",&in[i]);
		for(int i=1;i<=n;i++) scanf("%d",&cnt[i]);
		
		for(int i=1;i<=n;i++)
		{
			for(int k=1;k<=m;k++) used[k]=0;
			for(int j=in[i];j<=m;j++)
				if(!vis[j]&&vis[j-in[i]]&&used[j-in[i]]<cnt[i])
					vis[j]=1,used[j]=used[j-in[i]]+1;
		}
		
		for(int i=1;i<=m;i++) ans+=vis[i];
		
		printf("%d\n",ans);
	}
	
	return 0;
}
		
			
		
