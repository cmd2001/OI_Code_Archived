#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstdlib>
using namespace std;
int f[1010][1010];
int n,m,p,tmp;
int read()
{
	
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	n=read();
	m=read();
	if(n>=550&&m>=10)
	{
		printf("10\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		f[i][j]=i;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			for(int k=2;k<=m;k++)
			{
				f[i][k]=min(f[i][k],max(f[j-1][k-1],f[i-j][k])+1);
			}
		}
	}
	printf("%d\n",f[n][m]);
	return 0;
}
