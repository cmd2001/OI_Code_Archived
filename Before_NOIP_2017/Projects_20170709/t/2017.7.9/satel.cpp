#include<math.h>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
char s[80];
int n,m,cow,cnt=1,map[80][80],ma[80],vis[6400];
void dfs(int x,int y)
{
	map[x][y]=cnt;
	if(map[x-1][y]==1)
	{
		dfs(x-1,y);
	}
	if(map[x+1][y]==1)
	{
		dfs(x+1,y);
	}
	if(map[x][y-1]==1)
	{
		dfs(x,y-1);
	}
	if(map[x][y+1]==1)
	{
		dfs(x,y+1);
	}
}
int main()
{
	freopen("satel.in","r",stdin);
	freopen("satel.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		for(int j=1;j<=m;j++)
		{
			if(s[j-1]=='#')map[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(map[i][j]==1)
			{
				cnt++;
				dfs(i,j);
			}
		}
	}
	for(int i=1;i<=m;i++)ma[i]=map[1][i];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(map[i][j]!=ma[j])
			{
				if(vis[ma[j]]==0&&ma[j]!=0)vis[ma[j]]=1,cow++;
				ma[j]=map[i][j];
			}
		}
	}
	printf("%d\n",cow);
	printf("%d\n",cnt-cow-1);
	fclose(stdin);
	fclose(stdout);
}

