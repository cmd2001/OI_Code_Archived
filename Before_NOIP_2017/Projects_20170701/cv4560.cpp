#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e3+1e1,maxm=2e2+1e1;
const int mod=1000000007;

int dp[maxn][maxm][maxm],sum[maxn][maxm][maxm],n,m,k;
char a[maxn],b[maxm];

inline void getans()
{
	sum[0][0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i-1]==b[j-1])
				for(int kk=1;kk<=min(j,k);kk++)
				{
					dp[i][j][kk]=dp[i-1][j-1][kk]+sum[i-1][j-1][kk-1];
					sum[i][j][kk]=sum[i-1][j][kk]+dp[i][j][kk];
				}
			else
				for(int kk=1;kk<=min(j,k);kk++)
				{
					dp[i][j][kk]=0;
					sum[i][j][kk]=sum[i-1][j][kk];
				}
		}
	}
}
			
int main()
{
	scanf("%d%d%d%s%s",&n,&m,&k,a,b);
	getans();
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) for(int kk=0;kk<=k;kk++) cout<<dp[i][j][kk]<<" ";
	cout<<endl;
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) for(int kk=0;kk<=k;kk++) cout<<sum[i][j][kk]<<" ";
	cout<<endl;
	
	printf("%d\n",sum[n][m][k]);
	
	return 0;
}
