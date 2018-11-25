#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+10;
const double eps=1e-4;
int a[maxn],b[maxn];
double d[maxn];
int n,k;
double ans,l,r,mid;
bool test(double x)
{
	double s=0;
	for(int i=1;i<=n;i++) d[i]=a[i]-x*b[i];
	sort(d+1,d+1+n);
	for(int i=n;i>k;i--) s+=d[i];
	return (s>=0);
}

int main()
{
	while(scanf("%d%d",&n,&k)==2&&(n||k))
	{
		for(int i=1;i<=n;i++) scanf("%d",a+i);
		for(int i=1;i<=n;i++) scanf("%d",b+i);
		l=0,r=1;
        for(int i=1;i<=100;i++)
		{
			mid=(double)(l+r)/2;
			if(test(mid)) l=mid;
			else r=mid;
		}
		printf("%.0f\n",l*100);//You have to use %f to output double in POJ.
	}
	return 0;
}
