#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
	freopen("txt.txt","w",stdout);
	static long long int in,sq,cnt=0;
	for(in=1;in<=100;in++)
	{
		cnt=0;
		sq=in*in;
		for(long long int i=1,x;i<=in;i++)
		{
			x=sqrt(sq-i*i);
			if(x*x==sq-i*i) ++cnt;
		}
		printf("%lld %lld\n",in,4*cnt);
	}
	return 0;
}
