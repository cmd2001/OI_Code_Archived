#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e3+1e1,maxm=2e2+1e1;
const int mod=1000000007;

int dp[maxm][maxm],sum[maxm][maxm],n,m,k;
char a[maxn],b[maxm];

inline void getans()
{
	sum[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j;j--)
		{
			if(a[i-1]==b[j-1])
				for(int kk=min(k,j);kk;kk--)
				{
					dp[j][kk]=(dp[j-1][kk]+sum[j-1][kk-1])%mod;
					sum[j][kk]=(dp[j][kk]+sum[j][kk])%mod;
				}
			else
				for(int kk=min(k,j);kk;kk--)
				{
					dp[j][kk]=0;
				}
		}
	}
}
			
int main()
{
	scanf("%d%d%d%s%s",&n,&m,&k,a,b);
	getans();
	
	printf("%d\n",sum[m][k]);
	
	return 0;
}
