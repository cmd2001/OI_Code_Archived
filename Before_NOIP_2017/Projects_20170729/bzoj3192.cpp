#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lowbit(x) (x&(-x))
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int dat[maxn],in[maxn],n,m;
int row[maxn];
long long int ans;

bool cmp(int a,int b)
{
	return in[a]>in[b];
}
inline void update(int pos,int delta)
{
	while(pos<=n+m)
	{
		dat[pos]+=delta;
		pos+=lowbit(pos);
	}
}
inline int query(int pos)
{
	int ret=0;
	while(pos)
	{
		ret+=dat[pos];
		pos-=lowbit(pos);
	}
	return ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=n;i;i--) scanf("%d",in+i);
	for(int i=1;i<=m;i++) scanf("%d",in+n+i);
	debug<<"array in is"<<endl;
	for(int i=1;i<=n+m;i++) debug<<in[i]<<" ";
	debug<<endl;
	for(int i=1;i<=n+m;i++)
	{
		row[i]=i;
		update(i,1);
	}
	
	sort(row+1,row+1+n+m,cmp);
	
	for(int i=1;i<n+m;i++)
	{
		int l=row[i],r=row[i+1];
		if(l>r) l^=r^=l^=r;
		debug<<"l="<<l<<"r="<<r<<endl;
		ans+=query(r-1)-query(l);
		update(row[i],-1);
	}
	
	debug<<"ans="<<ans<<endl;
	
	ans++;
	debug<<"final ans="<<ans<<endl;
	
	return 0;
}
//http://blog.csdn.net/Oakley_/article/details/52824820
