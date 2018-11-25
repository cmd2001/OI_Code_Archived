#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int n,m;

struct SegmentTree
{
	int in[maxn],l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],st[maxn<<2],ed[maxn<<2],lazy[maxn<<2],cnt;
	int miv[maxn<<2],abo[maxn<<2];
	
	#define mid ((ll+rr)>>1)
	
	inline void build(int pos,int ll,int rr)
	{
		l[pos]=ll,r[pos]=rr;
		if(ll==rr)
		{
			abo[pos]=1;
			miv[pos]=in[ll];
			return;
		}
		build(lson[pos]=++cnt,ll,mid);
		build(rson[pos]=++cnt,mid+1,rr);
		miv[pos]=min(miv[lson[pos]],miv[rson[pos]]);
		abo[pos]=abo[lson[pos]]+abo[rson[pos]];
		//debug<<"pos="<<pos<<"abo="<<abo[pos]<<endl;
		
	}
	
	inline void chain(int pos)
	{
		if(miv[pos]>0) return;
		if(l[pos]==r[pos])
		{
			abo[pos]=0;
			lazy[pos]=0;
			return;
		}
		lazy[lson[pos]]+=lazy[pos],miv[lson[pos]]+=lazy[pos];
		lazy[rson[pos]]+=lazy[pos],miv[rson[pos]]+=lazy[pos];
		lazy[pos]=0;
		chain(lson[pos]);
		chain(rson[pos]);
		miv[pos]=0x3f3f3f3f;
		if(abo[lson[pos]]) miv[pos]=min(miv[pos],miv[lson[pos]]);
		if(abo[rson[pos]]) miv[pos]=min(miv[pos],miv[rson[pos]]);
		abo[pos]=abo[lson[pos]]+abo[rson[pos]];
		//debug<<"pos="<<pos<<"abo="<<abo[pos]<<endl;
	}
	inline void push(int pos)
	{
		if(lazy[pos]&&l[pos]!=r[pos])
		{
			lazy[lson[pos]]+=lazy[pos],miv[lson[pos]]+=lazy[pos];
			lazy[rson[pos]]+=lazy[pos],miv[rson[pos]]+=lazy[pos];
			lazy[pos]=0;
		}
	}
	
	inline void update(int pos,int ll,int rr,int x)
	{
		if(r[pos]<ll||l[pos]>rr) return;
		if(ll<=l[pos]&&r[pos]<=rr)
		{
			lazy[pos]+=x;
			miv[pos]+=x;
			chain(pos);
			return;
		}
		push(pos);
		update(lson[pos],ll,rr,x);
		update(rson[pos],ll,rr,x);
		miv[pos]=min(miv[lson[pos]],miv[rson[pos]]);
		abo[pos]=abo[lson[pos]]+abo[rson[pos]];
	}
	
	inline int query(int pos,int ll,int rr)
	{
		if(r[pos]<ll||l[pos]>rr) return 0;
		if(ll<=l[pos]&&r[pos]<=rr)
		{
			return abo[pos];
		}
		return query(lson[pos],ll,rr)+query(rson[pos],ll,rr);
	}
}SegT;

struct Tree
{
	int in[maxn];
	int st[maxn],ed[maxn],num[maxn],root,cnt;
	int s[maxn],t[maxn<<1],nxt[maxn<<1];
	bool vis[maxn];
	
	inline void addedge(int from,int to)
	{
		static int cnt=0;
		t[++cnt]=to;
		nxt[cnt]=s[from];
		s[from]=cnt;
	}
	
	
	inline void mem()
	{
		memset(vis,0,sizeof(vis));
		vis[root]=1;
	}
	
	inline int dfs(int pos)
	{
		st[pos]=num[pos]=++cnt;
		
		int at=s[pos],ret=st[pos];
		
		while(at)
		{
			if(!vis[t[at]])
			{
				vis[t[at]]=1;
				ret=max(ret,dfs(t[at]));
			}
			at=nxt[at];
		}
		
		return ed[pos]=ret;
	}
	
}Tree;

int main()
{
	freopen("alone1.in","r",stdin);
	freopen("my.txt","w",stdout);
	
	scanf("%d",&n);
	
	Tree.root=0;
	for(int i=1,org,fa;i<=n;i++)
	{
		scanf("%d%d",&org,&fa);
		//fa++;
		Tree.in[i]=org;
		Tree.addedge(fa,i);
	}
	
	Tree.dfs(Tree.root);
	
	for(int i=1;i<Tree.cnt;i++)
	{
		SegT.in[Tree.num[i]]=Tree.in[i];
	}
	
	/*debug<<"in of segT"<<endl;
	
	for(int i=1;i<=Tree.cnt;i++) debug<<SegT.in[i]<<" ";
	
	debug<<endl;*/
	
	SegT.build(SegT.cnt=1,1,Tree.cnt);
	
	//debug<<"Segment Tree Built"<<endl;
	
	scanf("%d",&m);
	
	for(int i=1,q,a,x;i<=m;i++)
	{
		scanf("%d%d",&q,&a);
		if(q==1)
		{
			scanf("%d",&x);
			
			SegT.update(1,Tree.st[a]+1,Tree.ed[a],-x);
		}
		else if(q==2)
		{
			printf("%d\n",SegT.query(1,Tree.st[a]+1,Tree.ed[a]));
		}
	}
	
	return 0;
}

