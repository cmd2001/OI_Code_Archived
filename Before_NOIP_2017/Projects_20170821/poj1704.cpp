#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+1e2;

int in[maxn],delta[maxn],n,x;

int main()
{
	static int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		
		for(int i=1;i<=n;i++) scanf("%d",in+i);
		
		sort(in+1,in+1+n);
		
		x=0;
		
		if(!(n&1))
			for(int i=2;i<=n;i+=2) x^=(in[i]-in[i-1]-1);
		else
			for(int i=1;i<=n;i+=2) x^=(in[i]-in[i-1]-1);
		
		if(x) puts("Georgia will win");
		else puts("Bob will win");
		
	}
		
	
	return 0;
}
