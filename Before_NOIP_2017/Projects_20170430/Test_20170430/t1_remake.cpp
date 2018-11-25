#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=610,maxm=810;
int n,m,to;
int ans[maxn][maxm][4],dp[maxn][maxm],from[maxn][maxm],tmp;
char rule[10],rul[10];

inline void getlin(int n,int m)
{
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
	{
		tmp=0;
		for(int k=1;k<=3;k++)
		{
			if(j-1>0) tmp+=abs(ans[i][j][k]-ans[i][j-1][k]);
			if(i-1>0) tmp+=abs(ans[i][j][k]-ans[i-1][j][k]);
		}
		dp[i][j]=dp[i-1][j],from[i][j]=0;
		if(j!=1&&dp[i][j]>dp[i-1][j-1]) dp[i][j]=dp[i-1][j-1],from[i][j]=-1;
		if(j!=m&&dp[i][j]>dp[i-1][j+1]) dp[i][j]=dp[i-1][j+1],from[i][j]=1;
		//printf("i=%d	j=%d	from=%d\n",i,j,from[i][j]);
		dp[i][j]+=tmp;
		//printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
	}
}
inline void getout(int n,int m)
{
	int pos=1;
	for(int i=1;i<=m;i++)
	{
		if(dp[n][i]<dp[n][pos]) pos=i;
	}
	for(int i=n;i>0;i--)
	{
		for(int j=pos;j<=m;j++)
			ans[i][j][1]=ans[i][j+1][1],
			ans[i][j][2]=ans[i][j+1][2],
			ans[i][j][3]=ans[i][j+1][3];
		pos+=from[i][pos];
	}
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch<='9'&&ch>='0')
	{
		ret=ret*10+ch-'0';
		ch=getchar();
	}
	return ret*fix;
}

int main()
{
	scanf("%s",rule);
	m=getint(),n=getint();
	scanf("%s",rul);
	to=m*2/3;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int k=1;k<=3;k++) ans[i][j][k]=getint();
	while(m>to)
	{
		getlin(n,m);
		getout(n,m);
		m--;
	}
	puts(rule);
	printf("%d %d\n",to,n);
	puts(rul);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) for(int k=1;k<=3;k++) printf("%d ",ans[i][j][k]);
		putchar('\n');
	}
	return 0;
}
	
