#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e6+1e2,maxm=3e6+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],len[maxn<<1];
bool vis[maxn];
int n,m,safe,ans,temp;

struct EDGE
{
	int a,b,safe,cost;
	friend bool operator < (const EDGE &a,const EDGE &b)
	{
		return a.safe>b.safe;
	}
}es[maxm];

struct fu_set
{
	int fa[maxn];
	inline void init()
	{
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	inline int findfa(int x)
	{
		return fa[x]==x?x:fa[x]=findfa(fa[x]);
	}
	inline void merge(int x,int y)
	{
		x=findfa(x),y=findfa(y);
		fa[x]=y;
	}
}fus;

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}
int main()
{
	n=getint(),m=getint();
	
	for(int i=1;i<=m;i++)
		es[i].a=getint(),es[i].b=getint(),es[i].safe=getint(),es[i].cost=getint();
	
	sort(es+1,es+1+m);
	
	fus.init();
	
	for(int i=1;i<=m;i++)
		if(fus.findfa(es[i].a)!=fus.findfa(es[i].b))
		{
			safe=es[i].safe;
			temp+=es[i].cost;
			fus.merge(es[i].a,es[i].b);
		}
	
	
	
	
	
	return 0;
}
	
			
	
