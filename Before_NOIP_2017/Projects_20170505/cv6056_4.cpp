#include<bits/stdc++.h>
using namespace std;
const int maxl=67,MOD=1000000000;
unsigned long long dp[maxl][maxl][maxl],mem[maxl][maxl],in,ans,lg;
int cnt;
unsigned long long int getint()
{
	unsigned long long int ret=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}

inline int calcbin(unsigned long long int num)
{
	int ret=0;
	while(num) num>>=1,++ret;
	return ret;
}
unsigned long long dfs(int rem,int last)
{
	if(rem==0) return 1;
	if(rem==1&&last!=0) return 0;
	if(!last) return 1;
	int pos=calcbin(rem);
	if(mem[pos][last]) return mem[pos][last];
	unsigned long long int ret=0;
	for(int k=pos;k>0;k--)
	{
		if(rem&((unsigned long long)1<<k))
		{
			for(int l=0;l<=pos;l++) for(int r=l;r<=pos;r++)
			{
				ret+=dfs(rem-((unsigned long long)1<<k),l)*dp[k][l][r];
				ret%=MOD;
			}
			mem[pos][last]=ret;
			return ret;
		}
	}
}
int main()
{
	in=getint();
	while(((unsigned long long)1<<lg)<in) ++lg;
	for(int i=0;i<=lg;i++) dp[i][i][i]=1;
	for(int i=0;i<=lg;i++)
		for(int j=0;j<i;j++)
			for(int k=j;k<i;k++)
			{
				if(i==j&&j==k) continue;
				for(int l=j;l<=k;l++)
				{
					if(l>i-1) continue;
					for(int r=l;r<=k;r++)
					{
						dp[i][j][k]+=dp[i-1][j][l]*dp[i-1][r][k];
						dp[i][j][k]%=MOD;
					}
				}
			}
	/*for(int i=0;i<=lg;i++)
	{
		printf("%d\n",1<<i);
		for(int j=0;j<=lg;j++)
			for(int k=0;k<=lg;k++)
				printf("dp[%d][%d]=%d\n",j,k,dp[i][j][k]);
	}*/
	cout<<dfs(in,calcbin(in))<<endl;
	return 0;
}
