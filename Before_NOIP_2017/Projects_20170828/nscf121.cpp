#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

int st[maxn],ed[maxn],delta[maxn],n,ans;

inline int getsta(int pos,int lim)
{
	if(lim<st[pos]) return 0;
	return ((min(lim,ed[pos])-st[pos])/delta[pos])+1;
}

inline int getsum(int lim)
{
	int ret=0;
	for(int i=1;i<=n;i++) ret+=getsta(i,lim);
	return ret;
}

inline void getans(int ll,int rr)
{
	int mid;
	while(rr>ll+1)
	{
		mid=(ll+rr)>>1;
		if(getsum(mid)&1) rr=mid;
		else ll=mid;
	}
	ans=rr;
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	static int t;
	t=getint();
	
	while(t--)
	{
		int rr=0;
		n=getint();
		
		for(int i=1;i<=n;i++)
			st[i]=getint(),
			rr=max(rr,ed[i]=getint()),
			delta[i]=getint();
		
		if(getsum(rr)&1)
		{
			getans(0,rr);
			printf("%d %d\n",ans,getsum(ans)-getsum(ans-1));
		}
		else puts("There's no weakness.");
	}
	
	return 0;
}
		
			

