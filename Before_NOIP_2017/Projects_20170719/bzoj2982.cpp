#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int mod=10007;

inline lli fastpow(lli base,lli tme,lli mod)
{
	lli ret=1,now=base%mod;
	while(tme)
	{
		if(tme&1)
		{
			ret*=now;
			if(ret>=mod) ret%=mod;
		}
		now*=now;
		if(now>=mod) now%=mod;
		tme>>=1;
	}
	return ret;
}
inline lli calc(lli n,lli m)
{
	if(n<m) return 0;
	
	lli above=1,below=1,rev;
	m=min(m,n-m);
	
	for(int i=1;i<=m;i++)
	{
		above*=(n-i+1);
		if(above>=mod) above%=mod;
		below*=i;
		if(below>=mod) below%=mod;
	}
	
	rev=fastpow(below,mod-2,mod);
	
	return above*rev%mod;
}
inline lli lucas(lli n,lli m)
{
	if(!m) return 1;
	return calc(n%mod,m%mod)*lucas(n/mod,m/mod)%mod;
}

int main()
{
	static lli t,n,m;
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		printf("%lld\n",lucas(n,m));
	}
	return 0;
}
	
	

