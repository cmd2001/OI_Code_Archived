#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=4e5+1e2;

int s[maxn],t[maxn],nxt[maxn];
int fa[maxn],cnt;
int in[maxn],ans[maxn],n,m,k;
bool vis[maxn];

inline void addedge(int from,int to)
{
	static int cnt=0;
	t[++cnt]=to;
	nxt[cnt]=s[from];
	s[from]=cnt;
}
inline int findfa(int x)
{
	return x==fa[x]?x:fa[x]=findfa(fa[x]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		a++,b++;
		addedge(a,b);
		addedge(b,a);
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&in[i]);
		in[i]++;
		vis[in[i]]=1;
	}
	for(int i=1;i<=n;i++) fa[i]=i;
	cnt=0;
	
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cnt++;
			int at=s[i];
			while(at)
			{
				const int &x=t[at];
				if((!vis[x])&&findfa(i)!=findfa(x)) fa[findfa(x)]=findfa(i),cnt--;
				at=nxt[at];
			}
		}
	}
	
	for(int i=k;i;i--)
	{
		ans[i]=cnt;
		const int &now=in[i];
		vis[now]=0;
		cnt++;
		int at=s[now];
		while(at)
		{
			const int &x=t[at];
			if((!vis[x])&&findfa(now)!=findfa(x)) fa[findfa(x)]=findfa(now),cnt--;
			at=nxt[at];
		}
	}
	
	printf("%d\n",cnt);
	for(int i=1;i<=k;i++) printf("%d\n",ans[i]);
	
	
	return 0;
}
	
	
		

