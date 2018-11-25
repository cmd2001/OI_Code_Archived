#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e2+1e1,maxm=1e4+1e2;

int in[maxn],n,m;
lli f[maxm];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",in+i);
	
	f[0]=1;
	
	for(int i=1;i<=n;i++)
		for(int j=m;j>=in[i];j--)
			f[j]+=f[j-in[i]];
	
	printf("%lld\n",f[m]);
	
	return 0;
}
