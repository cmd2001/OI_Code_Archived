#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxl=67,MOD=1000000000;
long long int x,ans=1;
int dp[maxl][maxl][maxl],l;
int tmp=0;

int main()
{
	scanf("%lld",&x);
	//debug<<"in="<<x<<endl;
	while(((unsigned long long int)1<<l)<x) ++l;
	//debug<<"l="<<l<<endl;
	dp[0][0][0]=1;
	for(int i=0;i<l;i++) dp[i][i][i]=1;
	for(int i=0;i<l;i++) for(int s=0;s<i;s++) for(int e=s;e<i;e++)	
	{
		if(i==s&&s==e) continue;
		for(int j=s;j<=e;j++) for(int k=j;k<=e;k++)
		{
			if(j>i-1) {dp[i][s][e]=0;continue;}
			dp[i][s][e]+=(long long int)dp[i-1][s][j]*dp[i-1][k][e]%MOD;
		}
	}
	//debug<<"ans="<<ans<<endl;
	while(x)
	{
		if(!(x&1)) x>>=1,++tmp;
		if(x&1) ans=ans*(dp[tmp][tmp][tmp]+1)%MOD;
		x>>=1,++tmp;
	}
	printf("%lld\n",ans);
	return 0;
}
