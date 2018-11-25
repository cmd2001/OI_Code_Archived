#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mem(x) memset(s,0,sizeof(s));
#define debug cout
using namespace std;
const int maxn=20,maxd=15;

int s[maxn];
int nxt[maxn],vis[maxn];
int now;
int mat[maxn][maxn];

inline void unz(int x)
{
	memset(s,0,sizeof(s));
	for(int i=1;i<=4;i++) if(x&(1<<(i-1))) s[i]=1;
}
inline int zip()
{
	int ret=0;
	for(int i=1;i<=4;i++) ret|=(nxt[i]<<(i-1));
	return ret;
}
	

inline void dfs(int pos)
{
	if(pos>4)
	{
		//for(int i=1;i<=4;i++) printf("%d",nxt[i]);
		//printf(" ");
		mat[now][zip()]=1;
		return;
	}
	if(vis[pos])
	{
		dfs(pos+1);
		return;
	}
	if(vis[pos+1]==0&&pos+1<=4)
	{
		vis[pos+1]=1;
		dfs(pos+1);
		vis[pos+1]=0;
	}
	nxt[pos]=1;
	dfs(pos+1);
	nxt[pos]=0;
	
}

inline void gen(int x)
{
	memset(nxt,0,sizeof(nxt));
	memset(vis,0,sizeof(vis));
	unz(x);
	for(int i=1;i<=4;i++) if(s[i]) vis[i]=1;
	dfs(1);
	
}

int main()
{
	for(int i=0;i<=15;i++)
	{
		//mem(s);mem(nxt);mem(vis);
		//debug<<"now = "<<i<<endl;
		now=i;
		gen(i);
		
		
		//putchar('\n');
	}
	printf("{\n");
	for(int i=0;i<16;i++)
	{
		printf("{");
		for(int j=0;j<15;j++) printf("%d,",mat[i][j]);
		printf("%d",mat[i][15]);
		puts("},");
	}
	puts("}");
}
	
	
 
