#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#define ll long long
#define mod 1000000007
#define inf 1000000000
using namespace std;
int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
int n,cnt;
ll ans=1;
int pri[1000005],mn[1000005],num[1000005];
bool del[1000005];
void getpri()
{
	for(int i=2;i<=n;i++)
	{
		if(!del[i])pri[++cnt]=i,mn[i]=cnt;
		for(int j=1;pri[j]*i<=n&&j<=cnt;j++)
		{
			del[pri[j]*i]=1;mn[pri[j]*i]=j;
			if(i%pri[j]==0)break;
		}
	}
}
void cal(int x)
{
	while(x!=1)
	{
		num[mn[x]]++;
		x/=pri[mn[x]];
	}
}
int main()
{
	n=read();
    getpri();
	for(int i=1;i<=n;i++)
		cal(i);
	for(int i=1;i<=cnt;i++)
		ans=ans*(num[i]*2+1)%mod;
	printf("%lld\n",ans);
	return 0;
}