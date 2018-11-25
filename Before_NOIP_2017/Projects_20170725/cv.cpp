#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],n,k;

inline bool check(int len)
{
	int ret=0;
	for(int i=1;i<=n;i++) ret+=in[i]/len;
	return ret>=k;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",in+i);
	
	int ll=0,rr=1e5,mid;
	
	while(rr>ll+1)
	{
		mid=(ll+rr)>>1;
		if(check(mid)) ll=mid;
		else rr=mid;
	}
	
	printf("%d\n",ll);
	
	return 0;
}
		
		

