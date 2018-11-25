#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+1e1;
int in[maxn][maxn],dp[maxn][maxn],n,m,ans;
int son[maxn][3],way[maxn][3],fa[maxn];
bool vis[maxn];

void getson(int pos)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(in[pos][i]&&!vis[i])
		{
			vis[i]=1;
			son[pos][++cnt]=i;
			way[pos][cnt]=in[pos][i];
			fa[i]=pos;
			getson(i);
		}
	}
}
void dfs(int pos)
{
	const int &lson=son[pos][1],&rson=son[pos][2],&lway=way[pos][1],&rway=way[pos][2];
	if(lson) dfs(lson);
	if(rson) dfs(rson);
	if(lson==0&&rson==0) {dp[pos][0]=0;return;}
	for(int i=0;i<n;i++) dp[pos][i+1]=max(dp[pos][i+1],dp[lson][i]+lway);
	for(int i=0;i<n;i++) dp[pos][i+1]=max(dp[pos][i+1],dp[rson][i]+rway);
	for(int i=0;i<n;i++) for(int k=0;k<n;k++)
	{
		if(i+k+2<=n) dp[pos][i+k+2]=max(dp[pos][i+k+2],dp[lson][i]+dp[rson][k]+lway+rway);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,x;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&x);
		in[a][b]=in[b][a]=x;
	}
	vis[1]=1;
	getson(1);
	dfs(1);
	for(int i=1;i<=m;i++) ans=max(ans,dp[1][i]);
	printf("%d\n",ans);
	return 0;
}
