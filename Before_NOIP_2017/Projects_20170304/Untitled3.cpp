#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=110;
int data[maxn][maxn];
int num[maxn],n,ans;
int used[maxn],at[maxn];
void gauss()
{
	int x;
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++) if(data[i][k]&&!used[i]) {x=i,used[i]=1;break;}
		at[k]=x;
		for(int i=1;i<=n;i++)
		{
			if(i!=x&&data[i][k])
			{
				for(int j=1;j<=n;j++) data[i][j]^=data[x][j];
				num[i]^=num[x];
			}
		}
	}
}
int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		memset(data,0,sizeof(data));
		memset(num,0,sizeof(num));
		memset(used,0,sizeof(used));
		memset(at,0,sizeof(at));
		ans=0;
		for(int i=1;i<=n;i++) data[i][i]=1,num[i]=1;
		for(int i=1,a,b;i<n;i++)
		{
			scanf("%d%d",&a,&b);
			data[a][b]=data[b][a]=1;
		}
		gauss();
		for(int i=1;i<=n;i++) ans+=num[at[i]];
		printf("%d\n",ans);
	}
	return 0;
}
		
	
