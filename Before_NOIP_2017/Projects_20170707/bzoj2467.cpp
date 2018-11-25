#include<bits/stdc++.h>
using namespace std;
const int mod=2007;

int t,n,ans;

inline int fastpow(int base,int tme)
{
	int ret=1,now=base%mod;
	while(tme)
	{
		if(tme&1)
		{
			ret*=now;
			if(ret>=mod) ret%=mod;
		}
		now*=now;
		if(now>=mod) now%=mod;
		tme>>=1;
	}
	return ret%mod;
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
	{
		ret=ret*10+ch-'0';
		ch=getchar();
	}
	return ret*fix;
}

int main()
{
	t=getint();
	while(t--)
	{
		n=getint();
		ans=fastpow(5,n-1);
		if(n>=mod) n%=mod;
		ans*=n;
		if(ans>=mod) ans%=mod;
		ans<<=2;
		if(ans>mod) ans%=mod;
		printf("%d\n",ans);
	}
	return 0;
}
