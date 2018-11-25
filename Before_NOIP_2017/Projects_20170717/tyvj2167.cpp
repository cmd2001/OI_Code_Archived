#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],n,m,ans;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",in+i);
	
	sort(in+1,in+1+n);
	
	for(int i=1;i<=n;i++)
	{
		if(m>=in[i]) m-=in[i],ans++;
		else break;
	}
	
	printf("%d\n",ans);
	
	return 0;
}
