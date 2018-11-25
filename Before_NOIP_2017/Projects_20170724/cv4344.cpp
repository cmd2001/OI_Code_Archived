#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

inline lli fastpow(lli base,lli tme,const lli &mod)
{
	lli now=base%mod,ret=1;
	while(tme)
	{
		if(tme&1) ret*=now,ret%=mod;
		now*=now;
		now%=mod;
		tme>>=1;
	}
	return ret;
}
inline lli getc(lli n,lli m,const lli &mod)
{
	if((!n)||m>n) return 0;
	lli above=1,below=1;
	for(int i=1;i<=m;i++)
	{
		above*=(n-m+1),above%=mod;
		below*=fastpow(m,mod-2,mod),below%=mod;
	}
	return above*below%mod;
}
inline lli lucas(lli n,lli m,const lli &mod)
{
	if(m>n) return 0;
	if(n<=mod&&m<=mod) return getc(n,m,mod);
	return lucas(n/mod,m/mod,mod)*getc(n%mod,m%mod,mod);
}

int main()
{
	static lli n,k,p,ans=0;
	cin>>n>>k>>p;
	for(lli i=k;i<=n;i+=k) ans+=lucas(n,i,p);
	cout<<ans<<endl;
	return 0;
}
	
	
