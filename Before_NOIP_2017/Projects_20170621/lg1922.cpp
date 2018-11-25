#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;

int siz[maxn],cnt[maxn],dp[maxn],n;
int s[maxn],t[maxn<<1],nxt[maxn<<1];
bool vis[maxn];

inline void addedge(int from,int to)
{
	static int cnt=0;
	t[++cnt]=to;
	nxt[cnt]=s[from];
	s[from]=cnt;
}
inline void doubleedge(int a,int b)
{
	addedge(a,b);
	addedge(b,a);
}

inline void pre(int pos)
{
	cnt[pos]=siz[pos]=1;
	int at=s[pos];
	while(at)
	{
		if(!vis[t[at]])
		{
			vis[t[at]]=1;
			pre(t[at]);
			siz[pos]+=siz[t[at]];
			if(siz[t[at]]==1) ++cnt[pos];
		}
		at=nxt[at];
	}
}
inline void dfs(int pos)
{
	dp[pos]=cnt[pos]>>1;
	int at=s[pos];
	while(at)
	{
		if(!vis[t[at]])
		{
			vis[t[at]]=1;
			dfs(t[at]);
			dp[pos]+=dp[t[at]];
		}
		at=nxt[at];
	}
}

inline void getans()
{
	vis[1]=1;
	pre(1);
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	dfs(1);
}

int main()
{
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		doubleedge(a,b);
	}
	
	getans();
	
	printf("%d\n",dp[1]);
	
	return 0;
}

			
	

