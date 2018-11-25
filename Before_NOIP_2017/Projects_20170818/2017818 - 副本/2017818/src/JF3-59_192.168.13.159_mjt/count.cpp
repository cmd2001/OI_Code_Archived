#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn =100010;
const int wei =15;
int dp[15][maxn];
int solve(int n,int m){
	memset(dp,0,sizeof(dp));
	dp[15][1]=1;
	dp[12][1]=1;
	dp[3][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=wei;j++){
			dp[j][i]=(dp[j][i]+dp[wei^j][i-1])%m;
			if(j==6||j==12||j==3)dp[j][i]=(dp[j][i]+dp[0][i])%m;
			else if(j==15)dp[j][i]=(dp[3][i-1]+dp[12][i-1]+dp[0][i]+dp[9][i])%m;
			
		}
	}
	return dp[15][n];
}
int main(){
	int n,m;
	while(true){
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)break;
		printf("%d\n",solve(n,m));
	}
	return 0;
}
