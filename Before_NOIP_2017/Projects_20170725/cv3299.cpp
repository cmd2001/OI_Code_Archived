#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e6+1e2;

int a[maxn<<1],b[maxn<<1],n,m,k;
inline void merge()
{
	int al=n,bl=m,pos=m+n;
	while(al&&bl)
	{
		if(a[al]>b[bl]) a[pos--]=a[al--];
		else a[pos--]=b[bl--];
	}
	while(al) a[pos--]=a[al--];
	while(bl) a[pos--]=b[bl--];
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=m;i++) scanf("%d",b+i);
	
	merge();
	
	printf("%d\n",a[k]);
	
	return 0;
}
