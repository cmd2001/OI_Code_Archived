#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

lli phi(lli x)
{
	lli ret=x;
	for(lli i=2;i*i<=x;i++)
	{
		if(!(x%i))
		{
			ret/=i;
			ret*=i-1;
			while(!(x%i)) x/=i;
		}
	}
	if(x!=1) ret/=x,ret*=x-1;
	return ret;
}

int main()
{
	static lli p;
	while(scanf("%lld",&p)==1)
	{
		printf("%lld\n",phi(phi(p)));
		//printf("%lld\n",phi(p-1));
	}
	return 0;
}
