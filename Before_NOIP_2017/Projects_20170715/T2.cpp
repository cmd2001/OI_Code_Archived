#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const double sq3=sqrt(3);

double h,w,r,d,pre;
int k;
lli p,q,tme,fix=0;
lli ans,sigma,tmp;

int main()
{
	scanf("%lf%lf%lf%d",&h,&w,&r,&k);
	d=r*2.0;
	p=w/d;
	if(p*d+r<=w) q=p;
	else q=p-1;
	//debug<<"p="<<p<<"q="<<q<<endl;
	if(h-2*r<0)
	{
		putchar('0');
		if(k) putchar(' '),putchar('0');
		putchar('\n');
		return 0;
	}
	tme=(h-2*r)/(sq3*r)+1;
	if(tme==1)
	{
		printf("%lld",p);
		if(k) putchar(' '),putchar('0');
		putchar('\n');
		return 0;
	}
	//debug<<"tme="<<tme<<endl;
	ans=(tme>>1)*(p+q)+(tme&1)*p;
	printf("%lld",ans);
	if(k)
	{
		if(p>=tme&&q>=tme) sigma=((tme*(tme+1))>>1)-1;
		else
		{
			//debug<<"now in else"<<endl;
			tmp=min(p,q);
			sigma=(tmp*(tmp+1)>>1)-1;
			tmp=tme-tmp;
			sigma+=(tmp>>1)*(p+q)+(tmp&1)*p;
		}
		//debug<<"\nnow sigma="<<sigma<<endl;
		printf(" %lld",sigma);	
	}
	putchar('\n');
	return 0;
}
	
	

