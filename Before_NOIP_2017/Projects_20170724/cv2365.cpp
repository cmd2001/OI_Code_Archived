#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

struct array_tree
{
	#define lowbit(x) (x&(-x))
	int t[maxn],n;
	array_tree()
	{
		memset(t,0,sizeof(t));
	}
	inline void init(int len)
	{
		n=len;
	}
	inline void update(int pos,int ope)
	{
		while(pos<=n)
		{
			t[pos]+=ope;
			pos+=lowbit(pos);
		}
	}
	inline int query(int pos)
	{
		int ret=0;
		while(pos)
		{
			ret+=t[pos];
			pos-=lowbit(pos);
		}
		return ret;
	}
}at;

struct node
{
	int pos;
	node* nxt;
}*nst[maxn],pool[maxn];
inline node* newnode()
{
	static int cnt=0;
	return *pool[++cnt];
}
inline void addnode(node* to,int pos)
{
	node* x=newnode();
	x->pos=pos;
	x->nxt=to->nxt;
	to->nxt=x;
}

int st[maxn],ed[maxn],ans[maxn];
int n,c,m;

inline void chain_alt(int x,int ope)
{
	node* pos=nst[x];
	while(pos)
	{
		at.update(pos->pos,ope);
		pos=pos->pos;
	}
}
int main()
{
	scanf("%d%d%d",&n,&c,&m);
	for(int i=1,t;i<=n;i++)
	{
		scanf("%d",&t);
		addnode(nst[t],i);
	}
	for(int i=1;i<=m;i++) scanf("%d%d",&st[i],&ed[i]);
	for(int i=1;i<=n;i)
	return 0;
}
	
	
