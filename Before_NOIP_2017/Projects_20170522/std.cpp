#include<bits/stdc++.h>
using namespace std;
#define lli long long int
#define lowbit(x) (x&-x)
#define debug cout
const int maxn=200000+10;
lli org[maxn],fix[maxn];
lli n,m;
void update(lli x,lli y,lli *to)
{
	while(x<=n)
	{
		to[x]+=y;
		x+=lowbit(x);
	}
}
lli query(lli x,lli *to)
{
	lli sum=0;
	while(x)
	{
		sum+=to[x];
		x-=lowbit(x);
	}
	return sum;
}
int main()
{
    freopen("dp.in","r",stdin);
    freopen("std.txt","w",stdout);
	scanf("%lld",&n);
	for(lli i=1,tmp,last=0;i<=n;i++)
	{
		scanf("%lld",&tmp);
		// debug<<"-=="<<tmp-last<<endl;
		update(i,tmp-last,org);
		update(i,(tmp-last)*i,fix);
		last=tmp;
	}
	scanf("%lld",&m);
	for(lli i=1,q,a,b,x;i<=m;i++)
	{
		scanf("%lld",&q);
		if(q==1)
		{
			scanf("%lld%lld%lld",&a,&b,&x);
			//debug<<a<<b<<x<<endl;
			update(a,x,org);
			update(b+1,-x,org);
			update(a,x*a,fix);
			update(b+1,-x*(b+1),fix);
		}
		else if(q==2)
		{
			scanf("%lld%lld",&a,&b);
			lli ans=0;
			ans+=(b+1)*query(b,org)-query(b,fix);
			//debug<<"+="<<ans<<endl;
			ans-=a*query(a-1,org)-query(a-1,fix);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
