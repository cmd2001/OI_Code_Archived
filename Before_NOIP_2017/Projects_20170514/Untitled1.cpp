#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mid ((ll+rr)>>1)
#define lowbit(x) (x&(-x))
using namespace std;
const int maxn=1e5+1e2,maxm=1e5+1e1;
int m,n,in[maxn];
long long int ans;
struct sigma_tree
{
	int l[8*maxn],r[8*maxn],lson[8*maxn],rson[8*maxn],mx[8*maxn],cnt;
	sigma_tree()
	{
		//Constructor function of this structure
		cnt=1;
	}
	void build(int ll,int rr,int pos)
	{
		l[pos]=ll,r[pos]=rr;
		if(ll==rr)
		{
			mx[pos]=in[ll];
			return;
		}
		build(ll,mid,lson[pos]=++cnt);
		build(mid+1,rr,rson[pos]=++cnt);
		mx[pos]=max(mx[lson[pos]],mx[rson[pos]]);
	}
	int query(int ll,int rr,int pos)
	{
		if(ll<=l[pos]&&r[pos]<=rr) return mx[pos];
		if(ll>r[pos]||rr<l[pos]) return -1;
		return max(query(ll,rr,lson[pos]),query(ll,rr,rson[pos]));
	}
}sig;
struct tree_array
{
	long long int dat[maxn];
	void update(int pos,int num)
	{
		while(pos<maxm) dat[pos]+=num,pos+=lowbit(pos);
	}
	long long int query(int pos)
	{
		long long int ret=0;
		while(pos) ret+=dat[pos],pos-=lowbit(pos);
		return ret;
	}
}tr;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&in[i]);
		tr.update(in[i],1);
		ans+=(i-tr.query(in[i]));
	}
	printf("%lld\n",ans);
	sig.build(1,n,1);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",sig.query(a,b,1));
	}
	return 0;
}

