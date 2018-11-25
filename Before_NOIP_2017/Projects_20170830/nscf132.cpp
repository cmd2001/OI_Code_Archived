#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e4+1e2;

int c[maxn],siz[maxn],maxl;
lli ans;

inline int getc(int x)
{
	int cnt=0;
	for(int i=2;i*i<=x;i++)
		if(!(x%i))
		{
			x/=i;
			++cnt;
			if(!(x%i)) return 0;
		}
	cnt+=(x>1);
	return (cnt&1)?-1:1;
}
inline void divi(int x)
{
	for(int i=1;i*i<=x;i++)
		if(!(x%i))
		{
			siz[i]++,maxl=max(maxl,i);
			if(i*i!=x) siz[x/i]++,maxl=max(maxl,x/i);
		}
}
inline lli c4(lli x)
{
	if(x<4) return 0;
	return x*(x-1)*(x-2)*(x-3)/24;
}
inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	static int n;
	for(int i=1;i<=10000;i++) c[i]=getc(i);
	while(scanf("%d",&n)==1)
	{
		memset(siz,0,sizeof(siz));
		ans=maxl=0;
		while(n--)
			divi(getint());
		for(int i=1;i<=maxl;i++) ans+=c4(siz[i])*c[i];
		
		printf("%lld\n",ans);
	}
	
	return 0;
}
			
	

