#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+1e2;

bool isprime[maxn];
int prime[maxn],cnt;
bool vis[maxn];
int f[maxn],n;

inline void gen()
{
	const int n=35;
	for(int i=2,j;i<=n;i++)
	{
		if(!isprime[i]) prime[++cnt]=i;
		for(j=1;j<=cnt&&i*prime[j]<=n&&i%prime[j];j++) isprime[i*prime[j]]=1;
		if(i*prime[j]<=n) isprime[i*prime[j]]=1;
	}
}

bool judge(int x)
{
	return !isprime[x];
}


void dfs(int dep)
{
	if(dep>n)
	{
		if(judge(f[1]+f[n]))
		{
			for(int i=1;i<=n;i++) printf("%d ",f[i]);
			puts("");
		}
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			if(judge(i+f[dep-1]))
			{
				f[dep]=i;	
				dfs(dep+1);
				f[dep]=0;
			}
			vis[i]=0;
		}
	}
}

int main()
{
	scanf("%d",&n);
	
	gen();
	
	f[vis[1]=1]=1;
	
	dfs(2);
	
	return 0;
}
