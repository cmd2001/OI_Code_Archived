#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxl=362880+1e2;

int f[5][5],cnt,x,y;
char way[maxl];
char s[20];

inline bool unsol()
{
	static int t[15];
	int k=0,ret=0;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			t[++k]=f[i][j];
	for(int i=1;i<=9;i++)
		for(int j=i+1;j<=9;j++)
			if(t[i]!=9&&t[j]!=9&&t[i]>t[j]) ret++;
	return ret&1;
}

inline int h()
{
	const int tarx[]={0,1,1,1,2,2,2,3,3,3},tary[]={0,1,2,3,1,2,3,1,2,3};
	int ret=0;
	
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			ret+=abs(i-tarx[f[i][j]])+abs(j-tary[f[i][j]]);
	
	return ret;
}



inline bool dfs(int dep,int lim)
{
	if(!h()) return 1;
	
	if(dep+h()>lim) return 0;
	
	if(x-1>=0)
	{
		swap(f[x][y],f[x-1][y]);
		x--;
		if(dfs(dep+1,lim))
		{
			way[++cnt]='u';
			return 1;
		}
		x++;
		swap(f[x][y],f[x-1][y]);
	}
	if(x+1<=3)
	{
		swap(f[x][y],f[x+1][y]);
		x++;
		if(dfs(dep+1,lim))
		{
			way[++cnt]='d';
			return 1;
		}
		
		x--;
		swap(f[x][y],f[x+1][y]);
	}
	if(y-1>=0)
	{
		swap(f[x][y-1],f[x][y]);
		y--;
		if(dfs(dep+1,lim))
		{
			way[++cnt]='l';
			return 1;
		}
		y++;
		swap(f[x][y-1],f[x][y]);
	}
	if(y+1<=3)
	{
		swap(f[x][y+1],f[x][y]);
		y++;
		if(dfs(dep+1,lim))
		{
			way[++cnt]='r';
			return 1;
		}
		y--;
		swap(f[x][y+1],f[x][y]);
	}
	return 0;
}

	
int main()
{
	
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			scanf("%s",s);
			if(*s=='x') f[i][j]=9,x=i,y=j;
			else f[i][j]=*s-'0';
		}
	
	if(unsol())
	{
		puts("unsolvable");
		return 0;
	}
	
	for(int i=1;i<=100;i++)
		if(dfs(0,i)) break;
	
		
	for(int i=cnt;i;i--) putchar(way[i]);
	
	puts("");
			
	
	return 0;
}
