#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e2;

int in[maxn][maxn],r,c;
bool vis[maxn][maxn];
int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};
int c1,c2,m,n;

bool judge(int x,int y,int dx,int dy)
{
	bool ret=1;
	for(int i=x;i<x+dx;i++)
		for(int j=y;j<y+dy;j++)
			ret&=in[i][j];
	if(!ret) return 0;

    for(int i=x;i<x+dx;i++) ret&=(!in[i][y-1]);
    for(int i=x;i<x+dx;i++) ret&=(!in[i][y+dy]);
    for(int j=y;j<y+dy;j++) ret&=(!in[x-1][j]);
    for(int j=y;j<y+dy;j++) ret&=(!in[x+dx][j]);

    return ret;
}

inline void getd(int x,int y)
{
    for(m=1;in[x+m][y];m++);
    for(n=1;in[x][y+n];n++);
}

inline void dfs(int x,int y)
{
    for(int i=1,tx,ty;i<5;i++)
    {
        tx=x+dx[i],ty=y+dy[i];
        if(in[tx][ty]&&!vis[tx][ty])
        {
            vis[tx][ty]=1;
            dfs(tx,ty);
        }
    }
}

inline void calc()
{
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
        {
            if(in[i][j]&&!vis[i][j])
            {
                vis[i][j]=1;
                dfs(i,j);
                getd(i,j);
                if(judge(i,j,m,n)) ++c1;
                else ++c2;
            }
        }
}

int main()
{
    static char s[maxn];
    scanf("%d%d",&r,&c);
    for(int i=1;i<=r;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=c;j++) in[i][j]=(s[j]=='#');
    }

    calc();

    printf("%d\n%d\n",c1,c2);

    return 0;
}


