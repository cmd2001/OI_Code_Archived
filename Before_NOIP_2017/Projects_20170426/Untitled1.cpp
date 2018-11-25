#include<bits/stdc++.h>
#define debug cout
#define inf 0x3f3f3f3f
#define uaf inf+1
using namespace std;
const int maxn=1e5+1e2,maxm=1e3+1e1;
struct tube
{
	int pos,l,h;
	friend bool operator < (const tube &a,const tube &b) {return a.pos<b.pos;}
}tb[maxn];
int n,m,k,at,up[maxn],down[maxn];
int dp[2][maxm],low[2][maxm];
int ans=inf,lastdis=0;
int main()
{
	//freopen("text.txt","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d%d",up+i,down+i);
	for(int i=1;i<=k;i++) scanf("%d%d%d",&tb[i].pos,&tb[i].l,&tb[i].h);
	sort(tb+1,tb+1+k);
	for(int i=1;i<=m;i++) dp[0][i]=low[0][i]=0;
	for(int i=1;i<=n;i++)
	{
		const int now=i&1,from=(i+1)&1;
		//debug<<"now="<<now<<endl;
		for(int j=0;j<=m;j++) dp[now][j]=low[now][j]=inf;
		for(int j=1;j<=m;j++)
		{
			if(j-up[i]>0) dp[now][j]=min(min(dp[now][j],dp[now][j-up[i]]+1),min(dp[from][j-up[i]]+1,low[from][j-up[i]]+1));
			if(j+down[i]<=m) low[now][j]=min(low[now][j],min(low[from][j+down[i]],dp[from][j+down[i]]));
			if(j==m)
			{
				for(int k=m;k>=m-up[i];k--)
				{
					dp[now][j]=min(min(dp[now][j],dp[now][k]+1),min(dp[from][k]+1,low[from][k]+1));
				}
			}
			
		}
		if(tb[at+1].pos==i)
		{
			at++;
			for(int j=1;j<=tb[at].l;j++) dp[now][j]=low[now][j]=uaf;
			for(int j=tb[at].h;j<=m;j++) dp[now][j]=low[now][j]=uaf;
		}
		for(int j=1;j<=m;j++) if(dp[now][j]<inf||low[now][j]<inf) {lastdis=at;break;}
	}
	const int now=n&1;
	for(int i=1;i<=m;i++) ans=min(ans,min(dp[now][i],low[now][i]));
	if(ans!=inf) printf("1\n%d\n",ans);
	else printf("0\n%d\n",lastdis);
	return 0;
}
