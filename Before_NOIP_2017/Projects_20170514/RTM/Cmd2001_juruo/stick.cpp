#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define debug cout
using namespace std;
const double eps=1e-8,pi=3.1415926535;
double l,n,c,nl;
bool un;
inline int judge(const double &a,const double &b)
{
	if(fabs(a-b)<=eps) return 0;
	return a>b?1:-1;
}
inline double getans()
{
	double ll=0,rr=l,x,R,alp;
	//while(rr-ll>1e-8)
	for(int i=1;i<=1000;i++)
	{
		x=(ll+rr)/2;
		//debug<<"x="<<x<<endl;
		R=(x*x+(l/2)*(l/2))/(2*x);
		//debug<<"R="<<R<<endl;
		alp=asin((l/2)/R);
		//debug<<"alp="<<alp<<endl;
		//debug<<"len="<<4*alp*R<<endl;
		//if(2*alp*R>nl) rr=x;
		if(judge(2*alp*R,nl)>=0) rr=x;
		else ll=x;
	}
	x=(ll+rr)/2;
	return x;
}
int main()
{
	freopen("stick.in","r",stdin);
	freopen("stick.out","w",stdout);
	scanf("%lf%lf%lf",&l,&n,&c);
	nl=(1+n*c)*l;
	//debug<<"nl="<<nl<<endl;
	//debug<<getans()<<endl;
	printf("%.3f\n",getans());
	fclose(stdin);
	fclose(stdout);
	return 0;
}

