#include<stdio.h>
int n,m,dp[6][2];
int main()
{
	int i,j;
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	while(scanf("%d%d",&n,&m),n&&m)
	{
		dp[0][1]=dp[1][1]=dp[3][1]=dp[4][1]=dp[5][1]=1;dp[2][1]=0;
		for(i=1;i<n;i++)
		{
			int on=i&1^1,oth=i&1;
			dp[0][on]=dp[0][oth]+dp[1][oth]+dp[3][oth]+dp[4][oth]+dp[5][oth];dp[0][on]%=m;
			dp[1][on]=dp[0][oth]+dp[4][oth];dp[1][on]%=m;
			dp[2][on]=dp[3][oth];dp[2][on]%=m;
			dp[3][on]=dp[0][oth]+dp[2][oth];dp[3][on]%=m;
			dp[4][on]=dp[0][oth]+dp[1][oth];dp[4][on]%=m;
			dp[5][on]=dp[0][oth];dp[5][on]%=m;
		}
		printf("%d\n",dp[0][n&1]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
