#include<bits/stdc++.h>
using namespace std;
const int maxn=10;
int f[maxn][maxn]; // 1 means can attack , 1024 means puted , 0 means nothing
int xx[maxn],yy[maxn],cnt;

inline void fill(int x,int y)
{
	f[x][y]=1024;
	for(int i=1;i<8;i++)
		if(i!=x) f[i][y]++;
	for(int j=1;j<8;j++)
		if(j!=y) f[x][j]++;
	for(int i=-8;i<9;i++)
		if( i && x+i>0 && y+i>0 && x+i<8 && y+i<8 )
			f[x+i][y+i]++;
	for(int i=-8;i<9;i++)
		if( i && x+i>=0 && y-i>0 && x+i<8 && y-i<8)
			f[x+i][y-i]++;
}
inline void refill(int x,int y)
{
	if(f[x][y]!=1024) puts("Fuck you!");
	f[x][y]=0;
	for(int i=1;i<8;i++)
		if(i!=x) f[i][y]--;
	for(int j=1;j<8;j++)
		if(j!=y) f[x][j]--;
	for(int i=-8;i<9;i++)
		if( i && x+i>0 && y+i>0 && x+i<8 && y+i<8 )
			f[x+i][y+i]--;
	for(int i=-8;i<9;i++)
		if( i && x+i>0 && y-i>0 && x+i<8 && y-i<8)
			f[x+i][y-i]--;
}
inline int judge()
{
	int ret=1;
	for(int i=1;i<=7;i++)
		for(int j=1;j<=7;j++)
			ret&=(bool)f[i][j];
	return ret;
}

inline void dfs(int tme,int lx)
{
	if(tme>4)
	{
		if(!judge()) return;
		printf("Solution %d :: ",++cnt);
		for(int i=1;i<=4;i++)
			printf("(%d,%d) ",xx[i],yy[i]);
		putchar('\n');
		//cnt++;
		return;
	}
	for(int i=lx;i<=7;i++)
		for(int j=1;j<=7;j++)
		{
			if(!f[i][j])
			{
				fill(i,j);
				xx[tme]=i,yy[tme]=j;
				dfs(tme+1,i+1);
				refill(i,j);
			}
		}
}

int main()
{
	dfs(1,1);
	
	
	printf("%d\n",cnt);
	return 0;
}
				
