#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e7+1e2;
int phi[maxn],prime[maxn],cnt,n;
bitset<maxn> vis;
lli sum[maxn],ans;

inline void getphi(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			prime[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
		{
			vis[i*prime[j]]=1;
			phi[i*prime[j]]=phi[i]*phi[prime[j]];
			if(!(i%prime[j]))
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
}

int main()
{
	scanf("%d",&n);
	
	phi[1]=1,vis[1]=1;
	getphi(n);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+phi[i];
	
	/*for(int i=1;i<=n;i++) debug<<phi[i]<<" ";
	debug<<endl;*/
	
	for(int i=1;i<=cnt;i++) ans+=(sum[n/prime[i]]<<1)-1;
	
	printf("%lld\n",ans);
	
	return 0;
}
	
	
	
