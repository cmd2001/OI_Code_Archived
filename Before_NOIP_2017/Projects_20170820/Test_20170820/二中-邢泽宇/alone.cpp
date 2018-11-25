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
	int in[maxn],l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],st[maxn<<2],ed[maxn<<2],lazy[maxn<<2],dat[maxn<<2],cnt;
	int nums[maxn<<4],delta[maxn<<2],pcnt;
	
	inline void array_merge(int* dst,int* a,int* b,int al,int bl)
	{
		int k=0,ap=0,bp=0;
		while(ap<=al&&bp<=bl)
			dst[k++]=a[ap]<b[bp]?a[ap++]:b[bp++];
		while(ap<=al)
			dst[k++]=a[ap++];
		while(bp<=bl)
			dst[k++]=b[bp++];
	}
	
	#define mid ((ll+rr)>>1)
	
	inline void build(int pos,int ll,int rr)
	{
		//debug<<"pos="<<pos<<"ll="<<ll<<"rr="<<rr<<endl;
		l[pos]=ll,r[pos]=rr;
		st[pos]=pcnt+1,ed[pos]=st[pos]+(rr-ll);
		pcnt=ed[pos];
		if(ll==rr)
		{
			nums[st[pos]]=in[ll];
			//debug<<"returning"<<endl;
			return;
		}
		build(lson[pos]=++cnt,ll,mid);
		build(rson[pos]=++cnt,mid+1,rr);
		array_merge(nums+st[pos],nums+st[lson[pos]],nums+st[rson[pos]],mid-ll+1,rr-mid);
	}
	
	inline void getd(int pos)
	{
		while(st[pos]+delta[pos]<=ed[pos]&&nums[st[pos]+delta[pos]]<=dat[pos]) delta[pos]++;
	}
	inline void push(int pos)
	{
		if(lazy[pos])
		{
			if(lson[pos])
			{
				lazy[lson[pos]]+=lazy[pos],dat[lson[pos]]+=lazy[pos];
				getd(lson[pos]);
			}
			if(rson[pos])
			{
				lazy[rson[pos]]+=lazy[pos],dat[rson[pos]]+=lazy[pos];
				getd(rson[pos]);
			}
			lazy[pos]=0;
		}
	}
	
	inline void update(int pos,int ll,int rr,int x)
	{
		if(r[pos]<ll||l[pos]>rr) return;
		if(ll<=l[pos]&&r[pos]<=rr)
		{
			lazy[pos]+=x;
			dat[pos]+=x;
			getd(pos);
			return;
		}
		push(pos);
		update(lson[pos],ll,rr,x);
		update(rson[pos],ll,rr,x);
	}
	
	inline int query(int pos,int ll,int rr)
	{
		if(r[pos]<ll||l[pos]>rr) return 0;
		if(ll<=l[pos]&&r[pos]<=rr)
		{
			/*debug<<"array of pos="<<endl;
			for(int i=st[pos];i<=ed[pos];i++) debug<<nums[i]<<" ";
			debug<<endl;
			debug<<"dat="<<dat[pos]<<endl;*/
			int ret=delta[pos];
			//ret--;
			//debug<<"now ret="<<ret<<endl;
			return r[pos]-l[pos]+1-ret;
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
		//debug<<"pos="<<pos<<endl; 
		st[pos]=num[pos]=++cnt;
		
		int at=s[pos],ret=st[pos];
		
		while(at)
		{
			//debug<<"t="<<t[at]<<endl;
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
	freopen("alone.in","r",stdin);
	freopen("alone.out","w",stdout);
	
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
	
	//debug<<"Tree.cnt="<<Tree.cnt<<endl;
	
	//if(Tree.cnt!=n+1) debug<<"Warning :: Cnt != N+1"<<endl;
	
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
			
			SegT.update(1,Tree.st[a]+1,Tree.ed[a],x);
		}
		else if(q==2)
		{
			//debug<<"st="<<Tree.st[a]+1<<"ed="<<Tree.ed[a]<<endl;
			printf("%d\n",SegT.query(1,Tree.st[a]+1,Tree.ed[a]));
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}

