#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=610,maxm=810;
int n,m,to;
int ene[maxn][maxm];
int ans[maxn][maxm][4];
int dp[maxn][maxm],from[maxn][maxm],out[maxn];
char rule[10],rul[10];
void getcal(int n,int m)
{
	memset(ene,0,sizeof(ene));
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int k=1;k<=3;k++)
	{
		if(j-1>0) ene[i][j]+=abs(ans[i][j][k]-ans[i][j-1][k]);
		if(i-1>0) ene[i][j]+=abs(ans[i][j][k]-ans[i-1][j][k]);
	}
	//for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) printf("ene[%d][%d]=%d\n",i,j,ene[i][j]);
}
void getlin(int n,int m)
{
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
	{
		dp[i][j]=dp[i-1][j],from[i][j]=0;
		if(j!=1&&dp[i][j]>dp[i-1][j-1]) dp[i][j]=dp[i-1][j-1],from[i][j]=-1;
		if(j!=m&&dp[i][j]>dp[i-1][j+1]) dp[i][j]=dp[i-1][j+1],from[i][j]=1;
		//printf("i=%d	j=%d	from=%d\n",i,j,from[i][j]);
		dp[i][j]+=ene[i][j];
		//printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
	}
}
void getout(int n,int m)
{
	int pos=1;
	for(int i=1;i<=m;i++)
	{
		if(dp[n][i]<dp[n][pos]) pos=i;
	}
	for(int i=n;i>0;i--)
	{
		out[i]=pos;
		pos+=from[i][pos];
	}
}
void cut(int n,int m)
{
	for(int i=1;i<=n;i++)
	{
		//debug<<"out="<<out[i]<<endl;
		for(int j=out[i];j<=m;j++)
		{
			ans[i][j][1]=ans[i][j+1][1];
			ans[i][j][2]=ans[i][j+1][2];
			ans[i][j][3]=ans[i][j+1][3];
		}
	}
}

int main()
{
	freopen("input.ppm","r",stdin);
	freopen("output.ppm","w",stdout);
	scanf("%s",rule);
	scanf("%d%d",&m,&n);
	scanf("%s",rul);
	to=m*2/3;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int k=1;k<=3;k++) scanf("%d",&ans[i][j][k]);
	while(m>to)
	{
		getcal(n,m);
		getlin(n,m);
		getout(n,m);
		cut(n,m);
		m--;
	}
	puts(rule);
	printf("%d %d\n",m,n);
	puts(rul);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) for(int k=1;k<=3;k++) printf("%d ",ans[i][j][k]);
		printf("\n");
	}
	fclose(stdout);
	return 0;
}
	
