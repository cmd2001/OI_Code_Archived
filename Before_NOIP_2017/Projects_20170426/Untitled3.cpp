#include<bits/stdc++.h>
using namespace std;
const int maxn=2e7+1e2;
bool vis[maxn];
int prime[maxn],cnt;
int calc(int x)
{
	int j;
	for(int i=2;i<=maxn;i++)
	{
		if(i==x) return ++cnt;
		if(!vis[i]) prime[++cnt]=i;
		for(j=1;j<=cnt&&i*prime[j]<maxn&&i%prime[j];j++) vis[i*prime[j]]=1;
		if(i*prime[j]<maxn) vis[i*prime[j]]=1;
	}
}
int main()
{
	int x;
	scanf("%d",&x);
	printf("%d\n",calc(x));
	return 0;
}
