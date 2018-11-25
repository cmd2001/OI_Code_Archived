#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;

lli n,xx,yy,mxx,mxy,mix,miy,d;

int main()
{
	scanf("%lld",&n);
	
	mxx=mxy=-0x3f3f3f3f;
	mix=miy=0x3f3f3f3f;
	
	while(n--)
	{
		scanf("%lld%lld",&xx,&yy);
		mxx=max(mxx,xx);
		mix=min(mix,xx);
		mxy=max(mxy,yy);
		miy=min(miy,yy);
	}
	
	d=max(mxx-mix,mxy-miy);
	
	printf("%lld\n",d*d);
	
	return 0;
}
		
