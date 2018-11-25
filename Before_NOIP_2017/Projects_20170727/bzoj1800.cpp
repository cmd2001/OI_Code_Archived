#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=25;

lli in[maxn],half,n;
lli ans,cnt;

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",in+i);
	for(int i=2;i<=n+1;i++) in[i]+=in[i-1];
	if(in[n]&1)
	{
		puts("0");
		return 0;
	}
	half=in[n]>>1;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++) if(in[j]==in[i]+half)
		{
			++cnt;
		}
	}
	ans=cnt*(cnt-1)>>1;
	printf("%lld\n",ans);
	return 0;
}
	
	
