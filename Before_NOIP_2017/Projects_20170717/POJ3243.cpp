#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#define lli long long int
using namespace std;

lli gcd(lli a,lli b)
{
	while(a%b)
	{
		a%=b;
		a^=b^=a^=b;
	}
	return b;
}
lli exgcd(lli a,lli b,lli x,lli y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	lli ret=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return ret;
}
lli fastpow(lli bas,lli tme,lli mod)
{
	lli ret=1,now=bas%mod;
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
	return ret%mod;
}
lli bsgs(lli bas,lli tar,lli mod)
{
	lli now=1;
	for(int i=0;i<=100;i++)
	{
		if(now==tar) return i;
		now*=bas;
		if(now>=mod) now%=mod;
	}
	
	map m,vis;
	vis[1]=1,m[1]=0;
	
	lli d=
	


//http://blog.csdn.net/MIKASA3/article/details/52101588?locationNum=1 
