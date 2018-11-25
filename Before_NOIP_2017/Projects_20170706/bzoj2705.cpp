#include<iostream>
#include<cstdio>
#include<cmath>
#define lli long long int 
#define debug cout
using namespace std;

lli n,ans;
inline lli phi(lli x)
{
	lli ret=x;
	int sq=sqrt(x);
	for(int i=2;i<=sq;i++)
	{
		if(!(x%i))
		{
			ret/=i,ret*=(i-1);
			while(!(x%i)) x/=i;
		}
	}
	if(x!=1)
	{
		ret/=x;
		ret*=(x-1);
	}
	return ret;
}

int main()
{
	scanf("%lld",&n);
	int sq=sqrt(n);
	for(int i=1;i<=sq;i++)
	{
		if(!(n%i))
		{
			ans+=(lli)i*phi(n/i);
			if(i*i!=n) ans+=(lli)(n/i)*phi(i);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
