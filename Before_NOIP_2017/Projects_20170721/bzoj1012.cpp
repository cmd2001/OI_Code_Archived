#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;
const int inf=0x3f3f3f;

int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],dat[maxn<<2],cnt;
int len,n,mod,t,in;
char c[10];

inline void build(int pos,int ll,int rr)
{
	#define mid ((ll+rr)>>1)
	l[pos]=ll,r[pos]=rr;
	if(ll==rr)
	{
		dat[pos]=-inf;
		return;
	}
	build(lson[pos]=++cnt,ll,mid);
	build(rson[pos]=++cnt,mid+1,rr);
}
inline void update(int pos,int tar,int arg)
{
	if(tar<l[pos]||tar>r[pos]) return;
	if(l[pos]==r[pos]&&l[pos]==tar)
	{
		dat[pos]=arg;
		return;
	}
	update(lson[pos],tar,arg);
	update(rson[pos],tar,arg); 
	dat[pos]=max(dat[lson[pos]],dat[rson[pos]]);
}
inline int query(int pos,int ll,int rr)
{
	if(rr<l[pos]||ll>r[pos]) return -inf;
	if(ll<=l[pos]&&rr>=r[pos]) return dat[pos];
	return max(query(lson[pos],ll,rr),query(rson[pos],ll,rr));
}

int main()
{
	scanf("%d%d",&n,&mod);
	build(cnt=1,1,n);
	
	for(int i=1;i<=n;i++)
	{
		scanf("%s%d",c,&in);
		if(*c=='A')
		{
			in=((lli)in+t)%mod;
			update(1,++len,in);
		}
		else if(*c=='Q')
		{
			printf("%d\n",t=query(1,len-in+1,len));
		}
	}
	
	return 0;
}

 
