#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int map[80][80],mx,my,size,n,m;
char s[100];
void dfs(int x,int y)
{
	size++;
	map[x][y]=2;
	mx=max(mx,x);
	my=max(my,y);
	if(x-1>=1&&map[x-1][y]==1)
	{
		dfs(x-1,y);
	}
	if(x+1<=n&&map[x+1][y]==1)
	{
		dfs(x+1,y);
	}
	if(y-1>=1&&map[x][y-1]==1)
	{
		dfs(x,y-1);
	}
	if(y+1<=m&&map[x][y+1]==1)
	{
		dfs(x,y+1);
	}
}
bool find(int stx,int sty,int edx,int edy)
{
	int i,j;
	for(i=stx;i<=edx;i++)
	{
		for(j=sty;j<=edy;j++)
		{
			if(map[i][j]!=2)	return false;
		}
	}
	return true;
}
int main()
{
	freopen("satel.in","r",stdin);
	freopen("satel.out","w",stdout);
	int i,j,fz,anscow=0,anshom=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",s);
		for(j=0;j<m;j++)
		{
			if(s[j]=='.')map[i][j+1]=0;
			else	map[i][j+1]=1;
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(map[i][j]==1)
			{
				mx=0,my=0,size=0;
				dfs(i,j);
				fz=(mx-i+1)*(my-j+1);
				if(fz==size&&find(i,j,mx,my)==true)	anshom++;
				else	anscow++;
			}
		}
	}
	printf("%d\n%d",anshom,anscow);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
