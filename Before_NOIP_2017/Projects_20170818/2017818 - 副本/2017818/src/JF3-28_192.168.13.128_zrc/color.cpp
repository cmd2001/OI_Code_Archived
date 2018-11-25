#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<math.h>
#include<iostream>
using namespace std;
unsigned int MX,ANS,f[20];
int n,t,ans[20],map[20][20],col[20],vis[20],in[20],v[20];
char s[30];
int calc()
{
	int flag=0,cnt=0,tot=0;
	for(int i=1;i<=n;i++)if(vis[i])flag=1,tot++;
	if(flag==0)return 0;
	memset(v,0,sizeof(v));
	memset(col,0,sizeof(col));	
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(map[i][j]&&vis[i]&&vis[j])in[i]++;
	for(int i=1;i<=n;i++)in[i]/=2;
	while(tot)
	{
		int mx=-1,pos=0;
		for(int i=1;i<=n;i++)
		{
			if(v[i]==0&&vis[i]&&in[i]>mx)
			{
				pos=i;
				mx=in[i];
			}
		}
		v[pos]=1;tot--;
		if(col[pos]==0)col[pos]=++cnt;
		for(int i=1;i<=n;i++)
		{
			if(vis[i]&&v[i]==0&&map[pos][i]==0)col[i]=col[pos];
			else if(vis[i]&&map[pos][i])in[i]--;
		}
	}
	return cnt;
}
int dfs(int pos)
{
	if(pos==(n+1))
	{
		int y=calc();
		ans[++t]=y;
		int cnt=1,mi=0;
		for(int i=1;i<=n;i++)
		{
			if(vis[i])mi+=cnt;
			cnt*=2;
		}
		ANS+=f[mi]*y;
		return 0;
	}
	vis[pos]=1;
	dfs(pos+1);
	vis[pos]=0;
	dfs(pos+1);
}
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		for(int j=0;j<strlen(s);j++)
		{
			if(s[j]=='1')map[i][j+1]=1;
			else map[i][j+1]=0;
		}
	}
	MX=1<<n;f[1]=233;for(int i=2;i<MX;i++)f[i]=f[i-1]*233;
	dfs(1);
	printf("%u",ANS);
	fclose(stdin);
	fclose(stdout);
}
