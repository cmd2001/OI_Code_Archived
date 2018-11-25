#include<stdio.h>
int r,c,house=0,bull=0;
char map[80][80];
bool vis[80][80];
int getl(int x,int y)
{
	int ans=y;
	while(ans<c&&map[x][ans]=='#') ans++;
	return ans-1;
}
int getw(int x,int y)
{
	int ans=x;
	while(ans<r&&map[ans][y]=='#') ans++;
	return ans-1;
}
void dfs(int x,int y)
{
	vis[x][y]=1;
	if(x&&map[x-1][y]=='#'&&!vis[x-1][y]) dfs(x-1,y);
	if(y&&map[x][y-1]=='#'&&!vis[x][y-1]) dfs(x,y-1);
	if(x<r-1&&map[x+1][y]=='#'&&!vis[x+1][y]) dfs(x+1,y);
	if(y<c-1&&map[x][y+1]=='#'&&!vis[x][y+1]) dfs(x,y+1);
	return;
}
int main()
{
	int i,j,l,w,p,q;
	freopen("satel.in","r",stdin);
	freopen("satel.out","w",stdout);
	scanf("%d%d",&r,&c);
	for(i=0;i<r;i++)
	{
		scanf("%s",map[i]);
	}
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(map[i][j]=='.') continue;
			if(vis[i][j]) continue;
			l=getl(i,j);
			w=getw(i,j);
			if(j)
			{
				for(p=i+1;p<=w;p++)
				{
					if(map[p][j-1]=='#')
					{
						bull++;
						dfs(i,j);
						goto end;
					}
				}
			}
			for(p=i;p<=w;p++)
			{
				for(q=j;q<=l;q++)
				{
					if(map[p][q]!='#')
					{
						bull++;
						dfs(i,j);
						goto end;
					}
				}
			}
//			printf("(%d,%d) ",i,j);
//			printf("%d %d\n",l,w);
			if(l<c-1)
			{
				for(p=i;p<=w;p++)
				{
					if(map[p][l+1]=='#')
					{
						bull++;
						dfs(i,j);
						goto end;
					}
				}
			}
			if(w<r-1)
			{
				for(p=j;p<=l;p++)
				{
					if(map[w+1][p]=='#')
					{
						bull++;
						dfs(i,j);
						goto end;
					}
				}
			}
			house++;
			dfs(i,j);
			end:;
		}
	}
	printf("%d\n%d\n",house,bull);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
5 8
#####..#
#####.##
......#.
.###...#
.###..##
*/
