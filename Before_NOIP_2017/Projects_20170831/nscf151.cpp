#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e2+1e1;

struct node
{
	int x,y;
	node(int xx,int yy)
	{
		x=xx,y=yy;
	}
};

int t,n,m,ans;
char in[maxn][maxn];
int f[maxn][maxn];

deque<node> q;

inline void push(int tx,int ty,int d,int len)
{
	if(f[tx][ty]>d+len)
	{
		f[tx][ty]=d+len;
		if(len) q.push_back(node(tx,ty));
		else q.push_front(node(tx,ty));
	}
}
	

inline void core_bfs(int x,int y)
{
	const int &dis=f[x][y];
	if(x-1>=0&&y-1>=0)
	{	
		if(in[x][y]=='\\')
			push(x-1,y-1,dis,0);
		else push(x-1,y-1,dis,1);
	}
	if(x+1<=n&&y+1<=m)
	{
		if(in[x+1][y+1]=='\\')
			push(x+1,y+1,dis,0);
		else push(x+1,y+1,dis,1);
	}
	if(x-1>=0&&y+1<=m)
	{
		if(in[x][y+1]=='/')
			push(x-1,y+1,dis,0);
		else push(x-1,y+1,dis,1);
	}
	if(x+1<=n&&y-1>=0)
	{
		if(in[x+1][y]=='/')
			push(x+1,y-1,dis,0);
		else push(x+1,y-1,dis,1);
	}
}

inline void getans()
{
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	q.push_back(node(0,0));
	while(!q.empty())
	{
		const int x=q.front().x,y=q.front().y;
		q.pop_front();
		core_bfs(x,y);
	}
	while(!q.empty()) q.pop_front();
}

inline void getin()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",in[i]+1);
}
			
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		getin();
		
		getans();
		
		if(f[n][m]==0x3f3f3f3f) puts("NO SOLUTION");
		else printf("%d\n",f[n][m]);
	}
	
	return 0;
}


