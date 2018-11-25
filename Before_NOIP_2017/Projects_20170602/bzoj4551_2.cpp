#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
int s[maxn],t[maxn],nxt[maxn],n,m;
int fa[maxn],son[maxn],siz[maxn],dep[maxn],top[maxn],lownode[maxn];
bool vis[maxn],marked[maxn];

inline void addedge(int from,int to)
{
	static int cnt=0;
	t[++cnt]=to;
	nxt[cnt]=s[from];
	s[from]=cnt;
}

inline void dfs1(int pos)
{
	dep[pos]=dep[fa[pos]]+1;
	siz[pos]=1;
	int at=s[pos];
	while(at)
	{
		if(!vis[t[at]])
		{
			vis[t[at]]=1;
			fa[t[at]]=pos;
			dfs1(t[at]);
			siz[pos]+=siz[t[at]];
			if(siz[t[at]]>siz[son[pos]]) son[pos]=t[at];
		}
		at=nxt[at];
	}
}

inline void dfs2(int pos)
{
	if(pos==son[fa[pos]]) top[pos]=top[fa[pos]];
	else top[pos]=pos;
	int at=s[pos];
	while(at)
	{
		if(!vis[t[at]])
		{
			vis[t[at]]=1;
			dfs2(t[at]);
		}
		at=nxt[at];
	}
}

inline void init()
{
	vis[1]=1;
	dfs1(1);
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	dfs2(1);
	lownode[1]=marked[1]=1;
}

inline void mark(int pos)
{
	if(!marked[top[pos]])
	{
		marked[top[pos]]=1;
		lownode[top[pos]]=pos;
		return;
	}
	if(dep[pos]<dep[lownode[top[pos]]]) lownode[top[pos]]=pos;
}

inline int query(int x)
{
	debug<<"x="<<x<<endl;
	debug<<"top="<<top[x]<<endl;
	while((!marked[top[x]])||dep[lownode[top[x]]]>dep[x]) x=fa[top[x]];
	return lownode[top[x]];
}

int main()
{
	scanf("%d%d",&n,&m);
	debug<<"n="<<n<<endl;
	for(int i=1,a,b;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	init();
	debug<<"inited"<<endl;
	for(int i=1;i<=n;i++) debug<<"pos="<<i<<"dep="<<dep[i]<<"fa="<<fa[i]<<"top="<<top[i]<<endl;
	char ope[10];
	for(int i=1,x;i<=m;i++)
	{
		scanf("%s%d",ope,&x);
		if(*ope=='C') mark(x);
		else if(*ope=='Q') printf("%d\n",query(x));
	}
	return 0;
}
			
