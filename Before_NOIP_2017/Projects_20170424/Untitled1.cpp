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
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d%d",up+i,down+i);
	for(int i=1;i<=k;i++) scanf("%d%d%d",&tb[i].pos,&tb[i].l,&tb[i].h);
	sort(tb+1,tb+1+k);
	for(int i=1;i<=m;i++) dp[0][i]=low[0][i]=0;
	for(int i=0;i<n;i++)
	{
		const int now=i&1,next=(i+1)&1;
		for(int j=0;j<=m;j++) dp[next][j]=low[next][j]=inf;
		for(int j=1;j<=m;j++)
		{
			if(j+up[i]<=m&&dp[now][j+up[i]]!=uaf) dp[now][j+up[i]]=min(dp[now][j+up[i]],dp[now][j]+1);
			if(j-down[i+1]>0) low[next][j-down[i+1]]=min(low[next][j-down[i+1]],min(low[now][j],dp[now][j]));
			//if(i+1==3&&j+up[i+1]==2) debug<<"dp32=================="<<endl<<"j="<<j<<"	"<<dp[now][1]<<endl;
			dp[next][min(j+up[i+1],m)]=min(dp[next][min(j+up[i+1],m)],min(dp[now][j],low[now][j])+1);
		}
		if(tb[at+1].pos==i+1)
		{
			at++;
			//if(i+1==2) debug<<"updating 2"<<endl<<"i="<<i<<endl;
			for(int j=1;j<=tb[at].l;j++) dp[next][j]=low[next][j]=uaf;
			for(int j=tb[at].h;j<=m;j++) dp[next][j]=low[next][j]=uaf;
		}
		for(int j=1;j<=m;j++) if(dp[next][j]<inf||low[next][j]<inf) {lastdis=at;break;}
	}
	const int now=n&1;
	for(int i=1;i<=m;i++) ans=min(ans,min(dp[now][i],low[now][i]));
	if(ans!=inf) printf("1\n%d\n",ans);
	else printf("0\n%d\n",lastdis);
	return 0;
}
