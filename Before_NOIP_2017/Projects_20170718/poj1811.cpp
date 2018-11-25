#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
const int lst[15]={0,2,3,5,7,11,13,17,19,23,29,31,61,24251},pn=13;
lli list[maxn],cnt;

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
	}
	return ret;
}


