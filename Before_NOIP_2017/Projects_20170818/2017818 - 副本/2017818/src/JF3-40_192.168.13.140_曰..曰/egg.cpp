#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define si scanf
#define so printf
#define N 
#define M 
#define INF  
template<typename TP>inline bool rd(TP& r)
{
	r=0;
	char tmp=getchar();
	while(tmp<'0'||tmp>'9')
	{
		if(tmp==EOF)
			return 0;
		tmp=getchar();
	}
	while('0'<=tmp&&tmp<='9')
	{
		r=(r<<3)+(r<<1)+tmp-'0';
		tmp=getchar();
	}
	return 1;
	
} 

long long n;
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	rd(n);
	so("%lld\n",ceil(2*sqrt(n)));
	
	
	return 0;	
	
} 
