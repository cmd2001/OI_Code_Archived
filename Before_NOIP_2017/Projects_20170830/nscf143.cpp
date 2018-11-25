#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int n,m,q;

struct fuset
{
	int fa[maxn];
	
	void init()
	{
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	int findfa(int x)
	{
		return x==fa[x]?x:fa[x]=findfa(fa[x]);
	}
	void merge(int x,int y)
	{
		x=findfa(x),y=findfa(y);
		fa[x]=y;
	}
}fus;

struct bininc
{
	int s[maxn],t[maxn<<1],l[maxn<<1],nxt[maxn<<1];
	int fa[maxn][22];
	int dat[maxn][22],dep[maxn];
	bool vis[maxn];
	
	inline void addedge(int from,int to,int len)
	{
		static int cnt=0;
		t[++cnt]=to;
		l[cnt]=len;
		nxt[cnt]=s[from];
		s[from]=cnt;
	}
	void dfs(int pos)
	{
		int at=s[pos];
		while(at)
		{
			if(!vis[t[at]])
			{
				vis[t[at]]=1;
				fa[t[at]][0]=pos;
				dat[t[at]][0]=l[at];
				dep[t[at]]=dep[pos]+1;
				dfs(t[at]);
			}
			at=nxt[at];
		}
	}
	void init()
	{
		memset(dat,0xef,sizeof(dat));
		memset(fa,-1,sizeof(fa));
		for(int i=1;i<=n;i++)
			if(!vis[i])
			{
				dep[i]=0;
				vis[i]=1;
				dfs(i);
			}
		for(int i=1;i<21;i++)
			for(int j=1;j<=n;j++)
				fa[j][i]=fa[fa[j][i-1]][i-1],
				dat[j][i]=max(dat[j][i-1],dat[fa[j][i-1]][i-1]);
	}
	int query(int x,int y) // x && y are in a same sub tree
	{
		int ret=-0x3f3f3f3f;
		if(dep[x]>dep[y]) swap(x,y);
		for(int i=20;i>=0;i--)
		{
			if(fa[y][i]!=-1&&dep[y]-(1<<i)>=dep[x])
			{
				ret=max(ret,dat[y][i]);
				y=fa[y][i];
			}
		}
		if(x==y) return ret;
		for(int i=20;i>=0;i--)
		{
			if(fa[x][i]!=-1&&fa[y][i]!=-1&&fa[x][i]!=fa[y][i])
			{
				ret=max(ret,max(dat[x][i],dat[y][i]));
				x=fa[x][i],y=fa[y][i];
			}
		}
		if(x!=y) ret=max(ret,max(dat[x][0],dat[y][0]));
		return ret;
	}
}binic;

struct edge
{
	int a,b,len;
	friend bool operator < (const edge &a,const edge &b)
	{
		return a.len<b.len;
	}
}e[maxn*3];

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}


int main()
{	
	n=getint(),m=getint();
	
	for(int i=1;i<=m;i++)
		e[i].a=getint(),e[i].b=getint(),e[i].len=getint();
	
	sort(e+1,e+1+m);
	fus.init();
	
	for(int i=1;i<=m;i++)
	{
		if(fus.findfa(e[i].a)!=fus.findfa(e[i].b))
		{
			fus.merge(e[i].a,e[i].b);
			binic.addedge(e[i].a,e[i].b,e[i].len);
			binic.addedge(e[i].b,e[i].a,e[i].len);
		}
	}
	
	binic.init();
	
	q=getint();
	
	for(int i=1,a,b;i<=q;i++)
	{
		a=getint(),b=getint();
		if(fus.findfa(a)!=fus.findfa(b)) puts("impossible");
		else printf("%d\n",binic.query(a,b));
	}
	
	return 0;
}
	
	
	
	
	
