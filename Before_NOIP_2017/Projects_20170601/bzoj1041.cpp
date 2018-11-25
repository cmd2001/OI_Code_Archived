#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;

lli r,ans;

inline lli gcd(lli a,lli b)
{
	while(a%b)
	{
		a%=b;
		a^=b^=a^=b;
	}
	return b;
}

inline lli issqu(lli x)
{
	lli sq=sqrt(x);
	return x==sq*sq;
}

int main()
{
	scanf("%lld",&r);
	for(lli d=1;d*d<=2*r;d++)
	{
		if(2*r%d==0)
		{
			for(lli u=1;u*u<=r/d;u++)
			{
				lli v=(2*r-d*u*u)/d;
				if(issqu(v)&&gcd(u,sqrt(v))==1) ++ans;
			}
			if(d*d!=2*r)
			{
				lli sq=sqrt(d/2);
				for(lli u=1;u<=sq;u++)
				{
					lli v=d-u*u;
					if(issqu(v)&&gcd(u,sqrt(v))==1&&u!=sqrt(v)) ++ans;
				}
			}
		}
	}
	++ans;
	printf("%lld\n",ans<<2);
	return 0;
}
				


