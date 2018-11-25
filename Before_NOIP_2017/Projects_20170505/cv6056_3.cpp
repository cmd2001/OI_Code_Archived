#include<bits/stdc++.h>
#define ulli unsigned long long int
#define debug cout
using namespace std;
const int maxl=67,MOD=1000000000;
ulli dp[maxl][maxl][maxl],mem[maxl][maxl],in,ans,lg;
int cnt;
ulli getint()
{
	ulli ret=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline int getlog(ulli rem)
{
	int ret=0;
	while(((ulli)1<<ret)<rem) ++ret;
	while(!(rem&((ulli)1<<ret))) ret--;
	return ret;
}
ulli dfs(ulli rem,int last)
{
	if(rem==1||rem==0||last==0) return 1;
	int dlg=getlog(rem);
	ulli ret=0;
	if(mem[dlg][last]) return mem[dlg][last];
	for(int l=0;l<=min(dlg,last);l++) for(int r=l;r<=min(dlg,last);r++) 
	{
		ret+=dfs(rem-((ulli)1<<dlg),l)*dp[dlg][l][r];
		ret%=MOD;
	}
	return mem[dlg][last]=ret;
}

int main()
{
	in=getint();
	while(((ulli)1<<lg)<in) ++lg;
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
	printf("%llu\n",dfs(in,lg));
	return 0;
}
