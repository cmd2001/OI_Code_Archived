#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e1+5e0;

int dp[maxn<<1][maxn][maxn];
int in[maxn][maxn],m,n;

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) scanf("%d",&in[i][j]);
	
	for(int i=0;i<=m+n-2;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=m;k++)
			{
				if(j==k) dp[i+1][j][k]=max(dp[i+1][j][k],dp[i][j][k]+in[j][i-j+1]);
				else dp[i+1][j][k]=max(dp[i+1][j][k],dp[i][j][k]+in[j][i-j+1]+in[k][i-k+1]);
			}
			
	debug<<"ans="<<dp[m+n-2][m][m]<<endl;
				
	
	return 0;
}
