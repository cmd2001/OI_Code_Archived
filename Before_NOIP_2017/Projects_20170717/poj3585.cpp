#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],v[maxn<<1];
int tme[maxn],fa[maxn],dp[maxn],root,cnt;
int ans;
bool vis[maxn];

inline void addedge(int from,int to,int val)
{
	++tme[to];
	t[++cnt]=to;
	v[cnt]=val;
	nxt[cnt]=s[from];
	s[from]=cnt;
}

inline void dfs(int pos)
{
	if(tme[pos]==1)
	{
		dp[pos]=inf;
		return;
	}
	int at=s[pos];
	while(at)
	{
		if(!vis[t[at]])
		{
			vis[t[at]]=1;
			fa[t[at]]=pos;
			dfs(t[at]);
			dp[pos]+=min(dp[t[at]],v[at]);
		}
		at=nxt[at];
	}
}
inline void getans(int pos,int edge)
{
	if(tme[pos]==1) return;
	if(pos!=root)
	{
		const int t=dp[pos]+min(dp[fa[pos]]-min(dp[pos],edge),edge);
		if(t>ans) ans=t;
	}
	int at=s[pos];
	while(at)
	{
		if(!vis[t[at]])
		{
			vis[t[at]]=1;
			getans(t[at],v[at]);
		}
		at=nxt[at];
	}
}
inline int findroot(int n)
{
	for(int i=1;i<=n;i++) if(tme[i]!=1) return i;
}
inline void init()
{
	memset(s,0,sizeof(s));
	memset(t,0,sizeof(t));
	memset(nxt,0,sizeof(nxt));
	memset(v,0,sizeof(v));
	memset(tme,0,sizeof(tme));
	memset(fa,0,sizeof(fa));
	memset(dp,0,sizeof(dp));
	root=cnt=ans=0;
}

int main()
{
	static int t,n;
	scanf("%d",&t);
	while(t--)
	{
		init();
		scanf("%d",&n);
		for(int i=1,a,b,v;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&v);
			addedge(a,b,v);
			addedge(b,a,v);
		}
		root=findroot(n);
		memset(vis,0,sizeof(vis));
		vis[root]=1;
		dfs(root);
		ans=dp[root];
		memset(vis,0,sizeof(vis));
		vis[root]=1;
		getans(root,0);
		
		printf("%d\n",ans);
		
	}
	
	return 0;
}
		
		

