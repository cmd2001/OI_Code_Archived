#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int lst[maxn],siz[maxn],rem,cnt;

inline void dvi(lli x)
{
	for(lli i=2;i*i<=x;i++)
	{
		if(!(x%i))
		{
			lst[++cnt]=i;
			while(!(x%i)) siz[cnt]++,x/=i;
		}
	}
	if(x!=1)
		lst[++cnt]=x,siz[cnt]=1;
}

map<int,lli> mem;

lli dfs()
{
	if(rem==1) return 1;
	if(mem.find(rem)!=mem.end()) return mem[rem];
	lli ret=0;
	for(int i=1;i<=cnt;i++)
	{
		if(siz[i])
		{
			siz[i]--;
			rem/=lst[i];
			ret+=dfs();
			siz[i]++;
			rem*=lst[i];
		}
	}
	return mem[rem]=ret;
}

int main()
{
	static int n,sum;
	static int ans;
	while(scanf("%d",&n)==1)
	{
		memset(lst,0,sizeof(lst));
		memset(siz,0,sizeof(siz));
		sum=ans=cnt=0;
		rem=n;
		
		dvi(n);
		
		for(int i=1;i<=cnt;i++) sum+=siz[i];
		
		ans=dfs();
		
		printf("%d %d\n",sum,ans);
	}
	
	return 0;
}
	
