#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxl=5e5+1e2;

lli base[maxn],cnt;
lli nums[maxl],len;

inline void gen(lli x)
{
	if(x>1000000000000LL) return;
	if(x) base[++cnt]=x;
	gen(x*10+4);
	gen(x*10+7);
}

inline void dfs(lli x,int pos,lli lim)
{
	if(x<=lim) nums[++len]=x;
	else  return;
	for(int i=1;i<=pos;i++)
		if((long double)x*base[i]<=lim)
			dfs(x*base[i],i,lim);
}

inline void pre(lli lim)
{
	for(int i=1;base[i]<=lim&&i<=cnt;i++)
		dfs(base[i],i,lim);
	sort(nums+1,nums+1+len);
	len=unique(nums+1,nums+1+len)-nums-1;
}

inline int calc(lli x)
{
	return upper_bound(nums+1,nums+1+len,x)-nums-1;
}

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	static int t=0;
	static lli a,b;
	
	gen(0);
	sort(base+1,base+1+cnt);
	pre((lli)1e12);
	
	t=getint();
	while(t--)
	{
		a=getint(),b=getint();
		
		printf("%d\n",calc(b)-calc(a-1));
	}
	
	
	return 0;
}
