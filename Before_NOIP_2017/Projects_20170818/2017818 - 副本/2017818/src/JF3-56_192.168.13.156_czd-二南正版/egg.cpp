#include<iostream>
#include<cstdio>
using namespace std;
long long dp[1010][1010];//j¸ö¼¦µ°i²ãÂ¥ 
long long m,n;
int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		dp[i][j]=i;
	}
	for(int i=1;i<=n;i++)
	for(int k=1;k<=i;k++)
	for(int j=2;j<=m;j++)
		dp[i][j]=min(dp[i][j],max(dp[k-1][j-1],dp[i-k][j])+1);
	 
	cout<<dp[n][m]<<endl;
	return 0;
}

