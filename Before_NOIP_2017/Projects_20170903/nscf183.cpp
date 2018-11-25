#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int val[maxn],deg[maxn],n,ans;
bool vis[maxn];
queue<int> q;

inline int dfs(int x)
{
	int ret=0;
	while(!vis[x])
	{
		vis[x]=1;
		ret++;
		x=val[x];
	}
	return ret>>1;
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	n=getint();
	for(int i=1;i<=n;i++) ++deg[val[i]=getint()];
	for(int i=1;i<=n;i++)
		if(!deg[i]) q.push(i);
	while(!q.empty())
	{
		const int pos=q.front();
		q.pop();
		vis[pos]=1;
		if(!vis[val[pos]])
		{
			++ans;
			vis[val[pos]]=1;
			if((!--deg[val[val[pos]]])&&(!vis[val[val[pos]]])) q.push(val[val[pos]]);
		}
	}
	for(int i=1;i<=n;i++) ans+=dfs(i);
	
	cout<< ans <<endl;
	
	return 0;
}
		

