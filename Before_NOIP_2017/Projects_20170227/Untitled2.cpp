#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+10;
const double eps=1e-3;
int a[maxn],b[maxn];
double d[maxn];
int n,k,out;
double ans,l,r,mid;
bool test(double x)
{
	double s=0;
	for(int i=1;i<=n;i++) d[i]=a[i]-x*b[i];
	//cout<<"dcalced"<<endl;
	sort(d+1,d+1+n);
	//cout<<"sorted"<<endl;
	for(int i=n;i>k;i--) s+=d[i];
	if(s>=0) return 1;
	else return 0;
}

int main()
{
	while(scanf("%d%d",&n,&k)==2&&n&&k)
	{
		for(int i=1;i<=n;i++) scanf("%d",a+i);
		//cout<<"ained"<<endl;
		for(int i=1;i<=n;i++) scanf("%d",b+i);
		//cout<<"bined"<<endl;
		l=0,r=1;
    while(l-r>eps)
		{
			mid=(l+r)/2;
			if(test(mid)) l=mid;
			else r=mid;
		}
		out=l*100;
		printf("%.0lf\n",l*100);
	}
	return 0;
}
