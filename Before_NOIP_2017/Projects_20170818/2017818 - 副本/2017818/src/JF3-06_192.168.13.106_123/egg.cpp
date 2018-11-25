#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1005;
int dp[MAXN][MAXN];
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	int n,m;
	cin>>n>>m;
//	dp[0][0]=1;		
//	for(int n=1;n<=10;n++)
//	for(int m=1;m<=10;m++)
//{
	for(int i=0;i<=m;i++)
	dp[1][i]=0;
	for(register int i=2;i<=n;i++)
	{
		dp[i][1]=i-1;
		for(register int j=2;j<=m;j++)
			{	
				int mx=0;
				int mn=9999999;
				for(register int k=2;k<=i;k++)
				{
						mx=max(dp[i-k+1][j],dp[k-1][j-1]);
						mn=min(mx,mn);		
				//		if(mn==0&&i==n&&j==m) cout<<k<<" ";			
				}
			dp[i][j]=mn+1;
		//	cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
	}
	cout<<dp[n][m];
//}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
