#include<bits/stdc++.h>
using namespace std;
const int maxn=5e7+1e2;
int prime[maxn],cnt,a,b,ans;
bool vis[maxn];

inline void get_prime()
{
	vis[1]=1;
	for(int i=2,j;i<maxn;i++)
	{
		if(!vis[i]) prime[++cnt]=i;
		for(j=1;j<=cnt&&i*prime[j]<maxn&&i%prime[j];j++) vis[i*prime[j]]=1;
		if(i*prime[j]<maxn) vis[i*prime[j]]=1;
	}
}

int main()
{
	get_prime();
	scanf("%d%d",&a,&b);
	for(int i=a;i<=b;i++) ans+=!vis[i];
	printf("%d\n",ans);
	return 0;
}
	
