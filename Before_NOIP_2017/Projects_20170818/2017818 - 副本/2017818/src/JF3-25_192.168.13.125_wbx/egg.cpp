#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int f[1010][1010];
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	int n,m,i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=m;j++)
		{
			f[i][j]=i;
		}
	}
	for(i=1;i<=n;i++)
	{
		for(k=1;k<=i;k++)
		{
			for(j=2;j<=m;j++)
			{
				f[i][j]=min(f[i][j],max(f[k-1][j-1],f[i-k][j])+1);
			}
		}
	}
	printf("%d",f[n][m]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
