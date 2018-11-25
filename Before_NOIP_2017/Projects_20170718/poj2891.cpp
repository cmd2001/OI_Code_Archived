#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

bool flag;
lli mod,res;

lli gcd(lli x,lli y)
{
	while(x%y)
	{
		x%=y;
		x^=y^=x^=y;
	}
	return y;
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
inline void calc(lli mod1,lli mod2,lli res1,lli res2)
{
	if(mod1==0||mod2==0)
	{
		flag=1;
		return;
	}
	mod=res=0;
	
	lli g=gcd(mod1,mod2),delta=res2-res1;
	if(delta%g)
	{
		flag=1;
		return;
	}
	
	mod=(mod1/g)*mod2;
	lli x,tmp;
	exgcd(mod1,mod2,x,tmp);
	
	const lli t=mod2/g;
	x=(delta/g)*x%t;
	if(x<0) x+=t;
	res=mod1*x+res1;
	
	if(res<0) res+=mod;
	
	//debug<<"res="<<res<<endl;
	
	return;
}

int main()
{
	static int k;
	static lli omod,ores,nmod,nres;
	
	//scanf("%*d");
	while(scanf("%d",&k)==1)
	{
		flag=0;
		scanf("%lld%lld",&omod,&ores);
		
		if(k==1)
		{
			printf("%lld\n",ores%omod);
			continue;
		}
		
		for(int i=2;i<=k;i++)
		{
			//debug<<"old mod="<<omod<<"old res="<<ores<<endl; 
			scanf("%lld%lld",&nmod,&nres);
			if(!flag) calc(omod,nmod,ores,nres);
			omod=mod,ores=res;
		}
		//debug<<"calc finished"<<endl;
		
		if(flag) puts("-1");
		else printf("%lld\n",res);
		
	}
	
	return 0;
}
