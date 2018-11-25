#include<bits/stdc++.h>
#define mid ((ll+rr)>>1)
#define debug cout
#define BINF -31000
using namespace std;
const int maxn=3e4+1e2;

int m,n;
int s[maxn],t[2*maxn],nxt[2*maxn];
int fa[maxn],son[maxn],siz[maxn],dep[maxn],top[maxn],num[maxn],in[maxn];
int l[8*maxn],r[8*maxn],lson[8*maxn],rson[8*maxn],mx[8*maxn],dat[8*maxn],mem[maxn],ptr[maxn],cnt;
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
void build(int pos,int ll,int rr);

void dfs1(int pos)
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
void dfs2(int pos)
{
	bool isleaf=1;
	if(pos==son[fa[pos]])
	{
		top[pos]=top[fa[pos]];
		num[pos]=num[fa[pos]]+1;
	}
	else
	{
		top[pos]=pos;
		num[pos]=1;
	}
	int at=s[pos];
	while(at)
	{
		if(!vis[t[at]])
		{
			isleaf=0;
			vis[t[at]]=1;
			dfs2(t[at]);
		}
		at=nxt[at];
	}
	if(isleaf)
	{
		int x=pos;
		while(top[x]==top[pos])
		{
			mem[num[x]]=in[x];
			x=fa[x];
		}
		build(ptr[top[pos]]=++cnt,num[top[pos]],num[pos]);
	}
}
//memcpy before build!!!
void build(int pos,int ll,int rr)
{
	l[pos]=ll,r[pos]=rr;
	if(ll==rr)
	{
		dat[pos]=mx[pos]=mem[ll];
		return;
	}
	build(lson[pos]=++cnt,ll,mid);
	build(rson[pos]=++cnt,mid+1,rr);
	dat[pos]=dat[lson[pos]]+dat[rson[pos]];
	mx[pos]=max(mx[lson[pos]],mx[rson[pos]]);
}
void update(int pos,int at)
{
	if(at<l[pos]||at>r[pos]) return;
	if(at==l[pos]&&at==r[pos])
	{
		dat[pos]=mx[pos]=mem[at];
		return;
	}
	update(lson[pos],at);
	update(rson[pos],at);
	dat[pos]=dat[lson[pos]]+dat[rson[pos]];
	mx[pos]=max(mx[lson[pos]],mx[rson[pos]]);
}
int qmax(int pos,int ll,int rr)
{
	if(rr<l[pos]||ll>r[pos]) return BINF;
	if(ll<=l[pos]&&rr>=r[pos]) return mx[pos];
	return max(qmax(lson[pos],ll,rr),qmax(rson[pos],ll,rr));
}
int qsum(int pos,int ll,int rr)
{
	if(rr<l[pos]||ll>r[pos]) return 0;
	if(ll<=l[pos]&&rr>=r[pos]) return dat[pos];
	return qsum(lson[pos],ll,rr)+qsum(rson[pos],ll,rr);
}
inline int getmax(int x,int y)
{
	int ret=max(in[x],in[y]);
	while(top[x]!=top[y])
	{
		if(dep[top[x]]>dep[top[y]])
		{
			ret=max(ret,qmax(ptr[top[x]],num[top[x]],num[x]));
			x=fa[top[x]];
		}
		else
		{
			ret=max(ret,qmax(ptr[top[y]],num[top[y]],num[y]));
			y=fa[top[y]];
		}
	}
	ret=max(ret,qmax(ptr[top[x]],min(num[x],num[y]),max(num[x],num[y])));
	return ret;
}
inline int getsum(int x,int y)
{
	int ret=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]>dep[top[y]])
		{
			ret+=qsum(ptr[top[x]],num[top[x]],num[x]);
			x=fa[top[x]];
		}
		else
		{
			ret+=qsum(ptr[top[y]],num[top[y]],num[y]);
			y=fa[top[y]];
		}
	}
	ret+=qsum(ptr[top[x]],min(num[x],num[y]),max(num[x],num[y]));
	return ret;
}

inline void init()
{
	vis[1]=1;
	dfs1(1);
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	dfs2(1);
}
inline void change(int pos,int x)
{
	in[pos]=x;
	mem[num[pos]]=x;
	update(ptr[top[pos]],num[pos]);
}

	
int main()
{
	static char c[10];
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		doubleedge(a,b);
	}
	for(int i=1;i<=n;i++) scanf("%d",in+i);
	init();
	scanf("%d",&m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%s%d%d",c,&x,&y);
		if(*c=='Q')
		{
			if(*(c+1)=='S') printf("%d\n",getsum(x,y));
			else if(*(c+1)=='M') printf("%d\n",getmax(x,y));
		}
		else if(*c=='C') change(x,y);
	}
	return 0;
}

