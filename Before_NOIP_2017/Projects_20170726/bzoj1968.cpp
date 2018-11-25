#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
using namespace std;

lli n,ans;

int main()
{
	scanf("%lld",&n);
	
	for(int i=1;i<=n;i++) ans+=(n/i); // the number of numbers in [1,n] % i == 0
	
	printf("%lld\n",ans);
	
	return 0;
}
	
