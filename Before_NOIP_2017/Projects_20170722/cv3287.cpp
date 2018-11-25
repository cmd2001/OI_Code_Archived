#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e4+1e2,maxm=5e5+1e2;

int n,m;
struct kruskal
{
	int fa[maxn];
	struct edge
	{
		int x,y,val;
		friend bool operator < (const edge &a,const edge &b)
		{
			return  a.val>b.val;
		}
	}e[maxm];
	bool vis[maxm];
	
	inline void init()
	{
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	int findfa(int x)
	{
		return x==fa[x]?x:fa[x]=findfa(fa[x]);
	}
	inline void work()
	{
		init();
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].val);
		}
		sort(e+1,e+1+m);
		for(int i=1;i<=m;i++)
		{
			const int &x=e[i].x,&y=e[i].y;
			if(findfa(x)!=findfa(y))
			{
				fa[findfa(x)]=findfa(y);
				vis[i]=1;
			}
		}
	}
}kru;

struct tree_cut
{
	int s[maxn],t[maxm<<1],nxt[maxm<<1];
	int top[]
		
