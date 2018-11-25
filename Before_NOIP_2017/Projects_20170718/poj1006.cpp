#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

lli res,mod;
inline lli gcd(lli a,lli b)
{
	while(a%b)
	{
		a%=b;
		a^=b^=a^=b;
	}
	return b;
}
lli exgcd(lli a,lli b,lli &x,lli &y)
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
inline void merge(lli mod1,lli mod2,lli res1,lli res2)
{
	lli g,x,y,delta=res2-res1;
	g=exgcd(mod1,mod2,x,y);
	mod=(mod1/g)*mod2;
	res=mod1*x*(delta/g)+res1;
	res%=mod;
}

int main()
{
	lli p,e,i,d,cnt=0;
	
	while(scanf("%lld%lld%lld%lld",&p,&e,&i,&d)==4)
	{
		if(p==-1&&e==-1&&i==-1&&d==-1) break;
		p%=23,e%=28,i%=33;
		merge(23,28,p,e);
		merge(mod,33,res,i);
		
		res-=d;
		while(res<=0) res+=mod;
		
		printf("Case %lld: the next triple peak occurs in %lld days.\n",++cnt,res);
	}
	
	return 0;
}


 
