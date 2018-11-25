#include<stdio.h>
#include<string.h>
#define int long long
int dp[20][120][10],dp0[20][120][10],check[10]={6,2,5,5,4,5,6,3,7,5},x,n;
int min(int a,int b)
{
	return a<b?a:b;
}
int mi(int n)
{
	int i,ans=1;
	for(i=0;i<n;i++)
	{
		ans*=10;
	}
	return ans;
}
void dp1()
{
	int i,j,k,p,q;
	for(i=x%10;i<=9;i++)
	{
		dp[1][check[i]][0]=i-x%10;
	}
	for(i=0;i<=9;i++)
	{
		if(i<x%10) dp[1][check[i]][1]=10+i-x%10;
		else dp[1][check[i]][1]=dp[i][check[i]][0]+10;
	}
	for(k=2;k<=9;k++)
	{
		for(i=0;i<=9;i++)
		{
			dp[1][check[i]][k]=dp[1][check[i]][k-1]+10;
		}
	}
	for(i=2;i<=n;i++)
	{
		for(j=2;j<120;j++)
		{
			int now=(x/mi(i-1))%10;
			for(p=now;p<=9;p++)
			{
				if(j-check[p]<0) continue;
				dp[i][j][0]=min(dp[i][j][0],dp[i-1][j-check[p]][p-now]);
			}
			for(p=0;p<=9;p++)
			{
				if(p<now)
				{
					if(j-check[p]<0) continue;
					dp[i][j][1]=min(dp[i][j][1],dp[i-1][j-check[p]][10+p-now]);
				}
				else dp[i][j][1]=min(dp[i][j][1],dp[i][j][0]+mi(i));
			}
			for(k=2;k<=9;k++)
			{
				dp[i][j][k]=dp[i][j][k-1]+mi(i);
			}
		}
	}
}
void dp2()
{
	int i,j,k,p,q;
	for(i=0;i<=9;i++)
	{
		dp0[1][check[i]][0]=i;
	}
	for(k=1;k<=9;k++)
	{
		for(i=0;i<=9;i++)
		{
			dp0[1][check[i]][k]=dp0[1][check[i]][k-1]+10;
		}
	}
	for(i=2;i<=n;i++)
	{
		for(j=2;j<120;j++)
		{
			for(p=0;p<=9;p++)
			{
				if(j-check[p]<0) continue;
				dp0[i][j][0]=min(dp0[i][j][0],dp0[i-1][j-check[p]][p]);
			}
			for(k=1;k<=9;k++)
			{
				dp0[i][j][k]=dp0[i][j][k-1]+mi(i);
			}
		}
	}
}
signed main()
{
	int i,j,k,y,find=0,init;
	freopen("DigitalCounter.in","r",stdin);
	freopen("DigitalCounter.out","w",stdout);
	scanf("%lld%lld",&n,&x);
	memset(dp,0x7f,sizeof(dp));
	memset(dp0,0x7f,sizeof(dp0));
	init=dp[0][0][0];
	for(i=0;i<n;i++)
	{
		find+=check[(x/mi(i))%10];
	}
	dp1();
	dp2();
//	for(i=0;i<=n;i++)
//	{
//		for(k=0;k<=9;k++)
//		{
//			for(j=0;j<22;j++)
//			{
//				printf("%lld ",dp[i][j][k]);
//			}
//			printf("\n");
//		}
//		printf("\n");
//	}
	if(dp[n][find][0]<init)
	{
		printf("%lld\n",dp[n][find][0]);
		fclose(stdin);
		fclose(stdout);
		return 0;
	}
	else
	{
		for(i=1;i<=n;i++)
		{
			if(dp0[i][find-check[0]*(n-i)][0]<init)
			{
				printf("%lld\n",dp0[i][find-check[0]*(n-i)][0]+mi(n)-x);
				fclose(stdin);
				fclose(stdout);
				return 0;
			}
		}
	}
}
/*
3
007
*/
