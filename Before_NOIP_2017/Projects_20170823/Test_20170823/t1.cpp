#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cerr
using namespace std;
const int maxn=1e6+1e2;
const int mod=1e9+7;
const int phi=1e9+6;

lli tme;
char s[maxn],l;

inline lli fastpow(lli base,lli tme,lli mod)
{
	lli ret=1,now=base%mod;
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
	scanf("%s",s+1);
	l=strlen(s+1);
	
	if(l==1&&s[1]=='1') return puts("1");
	
	for(int i=1;i<=l;i++) s[i]-='0';
	for(int i=1;i<=l;i++)
	{
		tme=tme*10+s[i];
		tme%=phi;
	}
	tme-=2;
	if(tme<0) tme+=phi;
	
	printf("%lld\n",fastpow(2,tme,mod));
	
	return 0;
}
