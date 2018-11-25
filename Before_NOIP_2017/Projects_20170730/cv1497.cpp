#include<cstdio>
#define lli long long int
using namespace std;

lli fastpow(const lli &bas,lli tme,const lli &mod)
{
	lli ret=1,now=bas%mod;
	while(tme)
	{
		if(tme&1) ret=ret*now%mod;
		now=now*now%mod;
		tme>>=1;
	}
	return ret;
}

int main()
{
	static lli bas,tme,mod;
	
	scanf("%lld%lld%lld",&bas,&tme,&mod);
	
	printf("%lld^%lld mod %lld=%lld\n",bas,tme,mod,fastpow(bas,tme,mod));
	
	return 0;
}
