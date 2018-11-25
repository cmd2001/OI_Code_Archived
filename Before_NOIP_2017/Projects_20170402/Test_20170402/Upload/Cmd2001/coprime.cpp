#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=110;
long long int lst[maxn],cnt,ans,x;
int t;
inline bool judge(register long long int x)
{
	if(x==1) return 1;
	for(int i=2,sq=sqrt(x);i<=sq;i++)
	{
		if(!(x%i)) return 1;
	}
	return 0;
}
inline void calc(register long long int x)
{
	for(int i=2;i<=x;i++)
	{
		if(!(x%i)) lst[++cnt]=i;
		while(!(x%i)) x/=i;
	}
}
inline void init()
{
	memset(lst,0,sizeof(lst));
	cnt=0;
	ans=0;
}
int main()
{
	freopen("coprime.in","r",stdin);
	freopen("coprime.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		init();
		scanf("%lld",&x);
		if(!judge(x)) {printf("%lld\n",x-1);continue;}
		ans=x;
		calc(x);
		for(int i=1;i<=cnt;i++) ans/=lst[i],ans*=(lst[i]-1);
		printf("%lld\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
