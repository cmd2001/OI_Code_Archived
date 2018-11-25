#include<bits/stdc++.h>
#define debug cout
#define mid ((ll+rr)>>1)
using namespace std;
const int maxn=2e5+1e2;
int l[8*maxn],r[8*maxn],lson[8*maxn],rson[8*maxn],dat[8*maxn],cnt;
int n,len,MOD;

inline void build(int pos,int ll,int rr)
{
	l[pos]=ll,r[pos]=rr;
	if(ll==rr)
	{
		if(rr<=len) scanf("%d",&dat[pos]);
		return;
	}
	build(lson[pos]=++cnt,ll,mid);
	build(rson[pos]=++cnt,mid+1,rr);
	dat[pos]=max(dat[lson[pos]],dat[rson[pos]]);
}

inline void update(int pos,int to,int num)
{
	if(to<l[pos]||to>r[pos]) return;
	if(l[pos]==r[pos]&&l[pos]==to)
	{
		dat[pos]=num;
		return;
	}
	update(lson[pos],to,num);
	update(rson[pos],to,num);
	dat[pos]=max(dat[lson[pos]],dat[rson[pos]]);
}

inline int query(int pos,int ll,int rr)
{
	if(rr<l[pos]||r[pos]<ll) return 0;
	if(ll<=l[pos]&&r[pos]<=rr) return dat[pos];
	return max(query(lson[pos],ll,rr),query(rson[pos],ll,rr));
}

int main()
{
	len=0;
	scanf("%d%d",&n,&MOD);
	build(++cnt,1,n);
	char c[5];
	for(int i=1,ope,t=0;i<=n;i++)
	{
		scanf("%s%d",c,&ope);
		if(*c=='A')
		{
			update(1,++len,(ope+t)%MOD);
		}
		else if(*c=='Q')
		{
			printf("%d\n",t=query(1,len+1-ope,len));
		}
	}
	return 0;
}
	
