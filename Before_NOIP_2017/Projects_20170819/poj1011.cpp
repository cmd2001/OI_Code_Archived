#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=70;

int in[maxn],n,sum,mx,len;
bool vis[maxn];

inline bool dfs(int pos,int lastl)
{
	bool lam=1;
	if(!lastl) lastl=len,pos=1;
	for(int i=pos;i<=n;i++)
	{
		lam&=vis[i];
		if(!vis[i]&&lastl-in[i]>=0)
		{
			vis[i]=1;
			if(dfs(i+1,lastl-in[i])) return 1;
			vis[i]=0;
			if(lastl-in[i]==0) return 0;
			if(lastl==len) return 0;
			while(in[i+1]==in[i]) i++;
		}
	}
	if(lastl==len&&lam) return 1;
	return 0;
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
	while(n=getint())
	{
		sum=mx=len=0;
		for(int i=1;i<=n;i++) sum+=(in[i]=getint()),mx=max(mx,in[i]);
		
		sort(in+1,in+1+n,greater<int>());
		
		for(int i=mx;i<=sum;i++)
		{
			if(sum%i==0)
			{
				memset(vis,0,sizeof(vis));
				if(dfs(1,len=i))
				{
					printf("%d\n",i);
					break;
				}
			}
		}
	}
	
	return 0;
}
