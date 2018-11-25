#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;

int n,m,f[1005][1005];

ll dp(int x,int y)
{
	if(!n)return 0;
	if(x==1)return 1;
	if(y==1)return x;
	if(y>=ceil(log2(x+1)))return ceil(log2(x+1));
	if(f[x][y]!=f[0][0])return f[x][y];
	for(int i=x;i;i--)
	{
		int t=max(dp(i-1,y-1),dp(x-i,y))+1;
		f[x][y]=min(t,f[x][y]);
	}
	return f[x][y];
}

int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	memset(f,0x3f,sizeof(f));
	printf("%d",dp(n,m));
	return 0;
}
