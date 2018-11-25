#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
#define debug cout
using namespace std;

lli f,n,x,y,mod,g,rev;

inline lli exgcd(lli a,lli b,lli &x,lli &y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	lli ret=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return ret;
}

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

/*inline lli fastpow(lli base,lli tme,lli mod)
{
	lli ret=1,now=base%mod;
	while(tme)
	{
		if(tme&1) ret=ret*now%mod;
		now=now*now%mod;
		tme>>=1;
	}
	return ret;
}*/

int main()
{
	n=getint(),mod=getint();
	
	f=1;
	
	for(int i=2;i<=n;i++)
	{
		exgcd(i+1,mod,x,y);
		f=f*(4*i-2)*x%mod;
		if(f<0) f+=mod;
	}
	
	if(n<34)
	{
		f=1;
		for(int i=2;i<=n;i++)
			f=f*(4*i-2)/(i+1)%mod;
	}
	
	
	
	printf("%lld\n",f);
	
	return 0;
}
