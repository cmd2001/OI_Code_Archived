#include <iostream>
#include <cstdio>  
using namespace std; 
int dp[1005][1005],m,n;
int main ()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    dp[1][i]=i;
    for(int j=2;j<=m;j++)
    for(int k=1;k<=n;k++)
    {
        dp[j][k]=max(0,dp[j][k-1])+1;
        for(int i=2;i<=k;i++)
        dp[j][k]=min(dp[j][k],max(dp[j-1][i-1],dp[j][k-i])+1);
    }
    printf("%d",dp[m][n]);
    return 0;
}
