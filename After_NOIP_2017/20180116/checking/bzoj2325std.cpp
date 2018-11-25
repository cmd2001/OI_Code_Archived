#include<bits/stdc++.h>
#define inf 1000000000
#define N 30005
#define M 80005
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int bin[25];
int n,m,cnt,place,sz;
int last[N];
int deep[N],fa[N][16],son[N],belong[N],pl[N];
char mp[N][2];
struct data{int l1,l2,r1,r2,d1,d2,d3,d4;};
struct edge{int to,next;}e[2*N];
struct seg
{
	int l,r;data d;
}t[4*N];
void insert(int u,int v)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
}
//左上到右上，左上到右下，左下到右上，左下到右下
data merge(data a,data b)
{
	data tmp;
	tmp.d1=max(a.d1+b.d1,a.d2+b.d3);if(tmp.d1<0)tmp.d1=-inf;
	tmp.d2=max(a.d1+b.d2,a.d2+b.d4);if(tmp.d2<0)tmp.d2=-inf;
	tmp.d3=max(a.d3+b.d1,a.d4+b.d3);if(tmp.d3<0)tmp.d3=-inf;
	tmp.d4=max(a.d3+b.d2,a.d4+b.d4);if(tmp.d4<0)tmp.d4=-inf;
	tmp.l1=max(a.d1+b.l1,a.d2+b.l2);tmp.l1=max(tmp.l1,a.l1);if(tmp.l1<0)tmp.l1=-inf;
	tmp.l2=max(a.d3+b.l1,a.d4+b.l2);tmp.l2=max(tmp.l2,a.l2);if(tmp.l2<0)tmp.l2=-inf;
	tmp.r1=max(b.d1+a.r1,b.d3+a.r2);tmp.r1=max(tmp.r1,b.r1);if(tmp.r1<0)tmp.r1=-inf;
	tmp.r2=max(b.d2+a.r1,b.d4+a.r2);tmp.r2=max(tmp.r2,b.r2);if(tmp.r2<0)tmp.r2=-inf;
	return tmp;
}
void build(int k,int l,int r)
{
	t[k].l=l;t[k].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
    build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void update(int k,int x,char mp[2])
{
	int l=t[k].l,r=t[k].r;
	if(l==r)
	{
		t[k].d.d1=t[k].d.d2=t[k].d.d3=t[k].d.d4=-inf;
		t[k].d.l1=t[k].d.l2=t[k].d.r1=t[k].d.r2=-inf;
		if(mp[0]=='.')t[k].d.d1=t[k].d.l1=t[k].d.r1=1;
		if(mp[1]=='.')t[k].d.d4=t[k].d.l2=t[k].d.r2=1;
		if(mp[0]=='.'&&mp[1]=='.')
			t[k].d.d2=t[k].d.d3=t[k].d.l1=t[k].d.l2=t[k].d.r1=t[k].d.r2=2;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(k<<1,x,mp);
	else update(k<<1|1,x,mp);
	t[k].d=merge(t[k<<1].d,t[k<<1|1].d);
}
data query(int k,int x,int y)
{
	int l=t[k].l,r=t[k].r;
	if(x==l&&y==r)return t[k].d;
	int mid=(l+r)>>1;
	if(mid>=y)
		return query(k<<1,x,y);
    else if(mid<x)
		return query(k<<1|1,x,y);
    else 
		return merge(query(k<<1,x,mid),query(k<<1|1,mid+1,y));
}
void dfs1(int x)
{
	son[x]=1;
	for(int i=1;i<=15;i++)
		if(deep[x]>=bin[i])
			fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=last[x];i;i=e[i].next)
	{
		if(e[i].to==fa[x][0])continue;
		fa[e[i].to][0]=x;
		deep[e[i].to]=deep[x]+1;
		dfs1(e[i].to);
		son[x]+=son[e[i].to];
	}
}
void dfs2(int x,int chain)
{
	pl[x]=++place;belong[x]=chain;
	update(1,pl[x],mp[x]);
	int k=0;
	for(int i=last[x];i;i=e[i].next)
	{
		if(e[i].to==fa[x][0])continue;
		if(son[e[i].to]>son[k])
			k=e[i].to;
	}
	if(k)dfs2(k,chain);
	for(int i=last[x];i;i=e[i].next)
	{
		if(e[i].to==k||e[i].to==fa[x][0])continue;
		dfs2(e[i].to,e[i].to);
	}
}
int lca(int x,int y)
{
    if(deep[x]<deep[y])swap(x,y);
    int t=deep[x]-deep[y];
    for(int i=0;i<=15;i++)
        if(bin[i]&t)x=fa[x][i];
    for(int i=15;i>=0;i--)
       if(fa[x][i]!=fa[y][i])
          x=fa[x][i],y=fa[y][i];
    if(x==y)return x;
    return fa[x][0];
}
data solveque(int x,int f,bool flag)//flag表示是否将f并进去
{
	data ans;
	ans.l1=ans.l2=ans.r1=ans.r2=0;
	ans.d1=ans.d4=ans.d2=ans.d3=0;
	while(belong[x]!=belong[f])
	{
		ans=merge(query(1,pl[belong[x]],pl[x]),ans);
		x=fa[belong[x]][0];
	}
	if(flag==1)
	{
		if(pl[f]+1<=pl[x])ans=merge(query(1,pl[f]+1,pl[x]),ans);
	}
	else ans=merge(query(1,pl[f],pl[x]),ans);
	return ans;
}
void que(int x,int y)
{
	if(mp[x][0]=='#'&&mp[x][1]=='#'){printf("0\n");return;}
	int f=lca(x,y);
	data a=solveque(x,f,1),b=solveque(y,f,0);
	swap(a.d2,a.d3);swap(a.l1,a.r1);swap(a.l2,a.r2);
	data ans=merge(a,b);
	printf("%d\n",max(ans.l1,ans.l2));
}
int main()
{
    //freopen("dat.txt","r",stdin);
    //freopen("std.txt","w",stdout);
	bin[0]=1;for(int i=1;i<=20;i++)bin[i]=(bin[i-1]<<1);
   	int n=read();m=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		insert(u,v);insert(v,u);
	}
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]);
	build(1,1,n);
	dfs1(1);dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		char ch[2];scanf("%s",ch);
		if(ch[0]=='Q')
		{
			int x=read(),y=read();que(x,y);
		}
		else 
		{
			int x=read();
			scanf("%s",mp[x]);
			update(1,pl[x],mp[x]);
		}
	}
	return 0;
}