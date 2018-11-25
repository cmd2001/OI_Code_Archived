#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
const int inf=0x3f3f3f3f;

int cost[maxn],n,ans,st,ed;
int in[maxn];
queue<int> q;

inline void push(int pos,int x)
{
	if(pos>=n) ans=min(ans,pos-n+x);
	else if(cost[pos]>x)
	{
		cost[pos]=x;
		q.push(pos);
	}
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
	memset(cost,0x3f,sizeof(cost));
	ans=inf;
	n=getint();
	for(int i=0;i<n;i++) in[i]=getint();
	if(in[0]+1>=n) ans=in[0]+1-n;
	else
	{
		cost[0]=cost[in[0]+1]=0;
		q.push(in[0]+1);
		while(!q.empty())
		{
			const int pos=q.front();
			q.pop();
			int t=pos;
			while(t<n)
			{
				t+=(in[t])+1;
				if(t<n&&cost[t]<cost[pos]) break;
				push(t,cost[pos]);
			}
			push(pos+1,cost[pos]+1);
			push(pos-1,cost[pos]+1);
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}

