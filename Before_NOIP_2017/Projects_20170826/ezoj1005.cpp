#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int prime[maxn],chain[maxn<<1],tme[maxn<<1],cnt;
bool vis[maxn<<1];
long long n,mod,ans=1;

inline void getprime(int n)
{
	for(int i=2,j;i<=n;i++)
	{
		if(!vis[i])
		{
			prime[++cnt]=i;
			chain[i]=cnt;
			//if(!chain[i]) debug<<"i="<<i<<endl;
		}
		for(j=1;j<=cnt&&i*prime[j]<=n&&i%prime[j];j++)
		{
			//if(i==67) debug<<"prime="<<prime[j]<<endl;
			//if(i*prime[j]==1943) debug<<"1943 exist"<<endl;
			vis[i*prime[j]]=1,chain[i*prime[j]]=j;
		}
		if(i*prime[j]<=n) vis[i*prime[j]]=1,chain[i*prime[j]]=j;
	}
}
inline void divide(int x,int ope)
{
	//debug<<"in divide x="<<x<<endl;
	while(x!=1)
	{
		tme[chain[x]]+=ope;
		//if(!prime[chain[x]]) debug<<"x="<<x<<"chain="<<chain[x]<<endl;
		x/=prime[chain[x]];
	}
}

int main()
{
	scanf("%lld%lld",&n,&mod);
	
	getprime(n<<1);
	//debug<<"prime got"<<endl;
	
	for(int i=n<<1;i>n;i--) divide(i,1);
	for(int i=1;i<=n;i++) divide(i,-1);
	//debug<<"n+1="<<n+1<<endl;
	divide(n+1,-1);
	
	for(int i=1;i<=cnt;i++)
		while(tme[i]--) ans=ans*prime[i]%mod;
	
	printf("%lld\n",ans);
	
	return 0;
}
	
	
		
