#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

lli c,n;
inline lli gcd(lli a,lli b)
{
	while(a%b)
	{
		a%=b;
		a^=b^=a^=b;
	}
	return b;
}
inline lli fastpow(lli base,lli tme)
{
	lli ret=1,now=base;
	while(tme)
	{
		if(tme&1) ret*=now;
		now*=now;
		tme>>=1;
	}
	return ret;
}
inline lli getans()
{
	lli ret=0;
	
	for(int i=1;i<=n;i++) ret+=fastpow(c,gcd(i,n));
	
	// now we consider the operate of reverse
	if(n&1) ret+=n*fastpow(c,(n>>1)+1); // one left mapping one right and a single point
	else ret+=(n>>1)*fastpow(c,(n>>1)+1) // reverse by point
				+(n>>1)*fastpow(c,(n>>1)); // reverse by edge
	ret/=(n<<1);
	
	return ret;
}

int main()
{
	while(scanf("%lld%lld",&c,&n)==2&&(c||n)) 
		printf("%lld\n",getans());
	
	return 0;
}
