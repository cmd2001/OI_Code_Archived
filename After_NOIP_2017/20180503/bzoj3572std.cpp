#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 300005
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int bin[20];
int n,m,q,cnt,dfn;
int fa[N][20],dep[N],last[N],id[N],size[N];
int a[N],b[N],f[N];
int top,s[N],c[N];
int rem[N],bel[N];
struct edge{
	int to,next,v;
}e[2*N];
bool cmp(int a,int b)
{
	return id[a]<id[b];
}
void insert(int u,int v)
{
	e[++cnt]=(edge){v,last[u]};last[u]=cnt;
}
void dfs(int x,int f)
{
	id[x]=++dfn;size[x]=1;
	for(int i=1;bin[i]<=dep[x];i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=last[x];i;i=e[i].next)
		if(e[i].to!=f)
		{
			fa[e[i].to][0]=x;
			dep[e[i].to]=dep[x]+1;
			dfs(e[i].to,x);
			size[x]+=size[e[i].to];
		}
}
int lca(int x,int y)
{
	if(dep[x]>dep[y])swap(x,y);
	int t=dep[y]-dep[x];
	for(int i=0;bin[i]<=t;i++)
		if(bin[i]&t)y=fa[y][i];
	for(int i=18;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return x==y?x:fa[x][0];
}
int dis(int a,int b)
{
	return dep[a]+dep[b]-2*dep[lca(a,b)];
}
void solve(int a,int b)
{
	int x=b,mid=b;
	for(int i=18;i>=0;i--)
		if(dep[fa[x][i]]>dep[a])x=fa[x][i];
	rem[a]-=size[x];
	if(bel[a]==bel[b])
	{
		f[bel[a]]+=size[x]-size[b];
		return;
	}
	for(int i=18;i>=0;i--)
	{
		int nxt=fa[mid][i];
		if(dep[nxt]<=dep[a])continue;
		int t1=dis(bel[a],nxt),t2=dis(bel[b],nxt);
		if(t1>t2||(t1==t2&&bel[b]<bel[a]))mid=nxt;
	}
	f[bel[a]]+=size[x]-size[mid];
	f[bel[b]]+=size[mid]-size[b];
}
void dfs1(int x)
{
	c[++dfn]=x;rem[x]=size[x];
	for(int i=last[x];i;i=e[i].next)
	{	
		dfs1(e[i].to);
		if(!bel[e[i].to])continue;
		int t1=dis(bel[e[i].to],x),t2=dis(bel[x],x);
		if((t1==t2&&bel[e[i].to]<bel[x])||t1<t2||!bel[x])
			bel[x]=bel[e[i].to];
	}
}
void dfs2(int x)
{
	for(int i=last[x];i;i=e[i].next)
	{	
		int t1=dis(bel[x],e[i].to),t2=dis(bel[e[i].to],e[i].to);
        if( (t1==t2&&bel[e[i].to]>bel[x]) ) puts("id check") , printf("%d %d %d\n",x,e[i].to,bel[x]);
		if((t1==t2&&bel[e[i].to]>bel[x])||t1<t2||!bel[e[i].to]) bel[e[i].to]=bel[x];
		dfs2(e[i].to);
	}	
}
void query()
{
	top=dfn=cnt=0;
	m=read();
	for(int i=1;i<=m;i++)a[i]=b[i]=read();
	for(int i=1;i<=m;i++)bel[a[i]]=a[i];
	sort(a+1,a+m+1,cmp);
	if(bel[1]!=1)s[++top]=1;
    for(int i=1;i<=m;i++)
	{
		int t=a[i],f=0;
		while(top>0)
		{
			f=lca(s[top],t);
			if(top>1&&dep[f]<dep[s[top-1]])
				insert(s[top-1],s[top]),top--;
			else if(dep[f]<dep[s[top]])
			{
				insert(f,s[top]);top--;break;
			}
			else break;
		}
		if(s[top]!=f)s[++top]=f;
		s[++top]=t;
	}
	while(top>1)insert(s[top-1],s[top]),top--;
	dfs1(1) , dfs2(1);
    for(int i=1;i<=dfn;i++) printf("%d ",bel[c[i]]); puts("");
	for(int i=1;i<=dfn;i++) for(int j=last[c[i]];j;j=e[j].next)solve(c[i],e[j].to);
	for(int i=1;i<=dfn;i++)f[bel[c[i]]]+=rem[c[i]] , printf("%d ",rem[c[i]]); puts("");
	for(int i=1;i<=m;i++)printf("%d ",f[b[i]]);puts("");
	for(int i=1;i<=dfn;i++)
		f[c[i]]=bel[c[i]]=last[c[i]]=rem[c[i]]=0;
}
int main()
{
	bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		insert(u,v);
		insert(v,u);
	}
	dfs(1,0);
	memset(last,0,sizeof(last));
	q=read();
	while(q--)query();
	return 0;
}