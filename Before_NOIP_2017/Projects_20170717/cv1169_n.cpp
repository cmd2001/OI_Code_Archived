#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e1+5e0;

int dp[maxn][maxn][maxn][maxn];
int in[maxn][maxn],m,n;

int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) scanf("%d",&in[i][j]);
	
	for(int x1=1;x1<=m;x1++)
		for(int y1=1;y1<=n;y1++)
			for(int x2=1;x2<=m;x2++)
				for(int y2=1;y2<=n;y2++)
				{
					const int t=max(max(dp[x1-1][y1][x2-1][y2],dp[x1-1][y1][x2][y2-1]),max(dp[x1][y1-1][x2-1][y2],dp[x1][y1-1][x2][y2-1]));
					if(x1==x2&&y1==y2) dp[x1][y1][x2][y2]=t+in[x1][y1];
					else dp[x1][y1][x2][y2]=t+in[x1][y1]+in[x2][y2];
				}
				
	printf("%d\n",dp[m][n][m][n]);
}
