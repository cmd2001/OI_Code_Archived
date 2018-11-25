#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,a[80][80],sum[80][80];
bool visit[80][80];
int q[5]={0,1,-1,0,0};
int w[5]={0,0,0,1,-1};
int mini,minj,maxi,maxj,ans1,ans2;
void dfs(int x,int y)
{
	visit[x][y]=true;
	mini=min(mini,x);
	minj=min(minj,y);
	maxi=max(maxi,x);
	maxj=max(maxj,y);
	for(int i=1;i<=4;i++)
	{
		if(visit[x+q[i]][y+w[i]]) continue;
		if(a[x+q[i]][y+w[i]]) dfs(x+q[i],y+w[i]);
	}
}
int main()
{
	freopen("satel.in","r",stdin);
	freopen("satel.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		char e[80];
		scanf("%s",&e);
		for(int j=0;j<m;j++)
		{
			if(e[j]=='.') a[i][j+1]=0;
			else a[i][j+1]=1;
			sum[i][j+1]=sum[i-1][j+1]+sum[i][j]-sum[i-1][j]+a[i][j+1];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(visit[i][j]||!a[i][j]) continue;
			mini=minj=80;
			maxi=maxj=0;
			dfs(i,j);
			mini--;
			minj--;
			if(sum[maxi][maxj]-sum[maxi][minj]-sum[mini][maxj]+sum[mini][minj]!=(maxi-mini)*(maxj-minj)) ans2++;
			else ans1++;
		}
	}
	cout<<ans1<<endl;
	cout<<ans2<<endl;
	fclose(stdin);
	fclose(stdout);
}
/*
5 8
#####..#
#####.##
......#.
.###...#
.###..##

6 18
..................
..#####.......##..
..#####......##...
..................
#.......###.....#.
#.....#####.......
*/
