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
	int st,ed,id;
	friend bool operator < (const node &a,const node &b)
	{
		return a.st<b.st;
	}
}qry[maxn];

int in[maxn],nxt[maxn],lst[maxn],ans[maxn],n,m,c,pos,l;

int main()
{
	scanf("%d%d%d",&n,&c,&m);
	at.init(n);
	for(int i=1;i<=n;i++) scanf("%d",in+i);
	for(int i=n;i;i--)
	{
		nxt[i]=lst[in[i]];
		lst[in[i]]=i;
	}
	for(int i=1;i<=c;i++)
	{
		if(nxt[lst[i]]) at.update(nxt[lst[i]],1);
	}
	for(int i=1;i<=m;i++) scanf("%d%d",&qry[i].st,&qry[i].ed),qry[i].id=i;
	
	//for(int i=1;i<=n;i++) debug<<"i="<<i<<"nxt="<<nxt[i]<<endl;
	
	
	sort(qry+1,qry+1+m);
	
	l=1;
	
	for(int i=1;i<=m;i++)
	{
		while(l<qry[i].st)
		{
			if(nxt[l])
			{
				at.update(nxt[l],-1);
			}
			if(nxt[nxt[l]]) at.update(nxt[nxt[l]],1);
			l++;
		}
		ans[qry[i].id]=at.query(qry[i].ed)-at.query(qry[i].st-1);
	}
	
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	
	return 0;
}
		
