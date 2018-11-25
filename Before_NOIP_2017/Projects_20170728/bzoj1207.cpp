#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e4+1e2;

int f[maxn],tme[maxn],x[maxn],y[maxn],m,ans;

int abs(int x)
{
	return x>0?x:-x;
}
int main()
{
	scanf("%*d%d",&m);
	for(int i=1;i<=m;i++) scanf("%d%d%d",tme+i,x+i,y+i);
	
	for(int i=1;i<=m;i++)
	{
		f[i]=1;
		for(int j=i-1;j;j--)
		{
			if(abs(x[i]-x[j])+abs(y[i]-y[j])<=tme[i]-tme[j]) f[i]=max(f[i],f[j]+1);
		}
		ans=max(ans,f[i]);
	}
	
	printf("%d\n",ans);
	
	return 0;
}
