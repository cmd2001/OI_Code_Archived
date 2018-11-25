#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const int maxd=1e5;

int c[10],s[10],tot;
lli dp[maxn],ans,x;

inline void dfs(int dep,int sel,int tar)
{
	if(tar<0) return;
	if(dep>4)
	{
		if(sel&1) ans-=dp[tar];
		else ans+=dp[tar];
		return;
	}
	dfs(dep+1,sel+1,tar-(s[dep]+1)*c[dep]);
	dfs(dep+1,sel,tar);
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
	for(int i=1;i<5;i++) c[i]=getint();
	tot=getint();
	
	dp[0]=1;
	for(int k=1;k<5;k++)
		for(int i=1;i<=maxd;i++)
			if(i-c[k]>=0) dp[i]+=dp[i-c[k]];
	
	for(int i=1;i<=tot;i++)
	{
		for(int k=1;k<5;k++) s[k]=getint();
		x=getint();
		ans=0;
		dfs(1,0,x);
		printf("%lld\n",ans);
	}
	return 0;
}
