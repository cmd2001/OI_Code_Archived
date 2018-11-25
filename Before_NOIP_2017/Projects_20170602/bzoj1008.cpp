#include<bits/stdc++.h>
#define lli long long int 
using namespace std;
const int mod=100003;

lli m,n;

lli fast_pow(lli base,lli tme)
{
	lli now=base%mod,ret=1;
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
	scanf("%lld%lld",&m,&n);
	printf("%lld\n",(fast_pow(m,n)-m*fast_pow(m-1,n-1)%mod+mod)%mod);
	return 0;
}
