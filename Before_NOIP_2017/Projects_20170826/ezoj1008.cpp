#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
using namespace std;
const int maxn=1e7+1e2;

lli rev[maxn],p,ans;

int main()
{
	scanf("%lld",&p);
	rev[1]=1;
	for(int i=2;i<p;i++)
		rev[i]=(p-p/i)*rev[p%i]%p;
	

	ans=0;
	for(int i=1;i<p;i+=2) ans^=rev[i];
	printf("%lld ",ans);
	ans=0;
	for(int i=2;i<p;i+=2) ans^=rev[i];
	printf("%lld ",ans);
	ans=0;
	for(int i=1;i<=p;i++) ans+=rev[i];
	printf("%lld\n",ans);
	
	return 0;
}


