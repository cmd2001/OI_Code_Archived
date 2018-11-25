#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=4e4+1e2;

int n;
lli phi[maxn],ans;
int prime[maxn],cnt;
bitset<maxn> vis;

inline void getphi()
{
	phi[1]=1;
	for(int i=2,j;i<=n;i++)
	{
		if(!vis[i])
		{
			prime[++cnt]=i;
			phi[i]=i-1;
		}
		for(j=1;j<=cnt&&i*prime[j]<=n&&i%prime[j];j++) vis[i*prime[j]]=1,phi[i*prime[j]]=phi[i]*(prime[j]-1);
		if(j<=cnt&&i*prime[j]<=n) vis[i*prime[j]]=1,phi[i*prime[j]]=phi[i]*prime[j];
	}
}
			
int main()
{
	scanf("%d",&n);
	
	if(n==1)
	{
		puts("1");
		return 0;
	}
	getphi();
	
	for(int i=2;i<n;i++) ans+=phi[i];
	
	ans<<=1;
	ans+=3;
	
	printf("%lld\n",ans);
	
	return 0;
}

