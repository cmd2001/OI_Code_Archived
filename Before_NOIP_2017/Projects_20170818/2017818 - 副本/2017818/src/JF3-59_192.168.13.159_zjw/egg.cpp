#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m;
int f[1003][1003];
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	cin>>n>>m;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)f[1][i]=i;
	for(int i=1;i<=m;i++)f[i][0]=0,f[i][1]=1;
	for(int i=2;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i>=log2(n+1))
			{
				int a=log2(n+1);
				if(a==(double)log2(n+1))
				{
					f[i][j]=a;
					continue;
				} 
				else 
				{
					f[i][j]=a+1;
					continue;
				}
			}
			for(int k=1;k<=j;k++)
			{
				f[i][j]=min(f[i][j],max(f[i][j-k],f[i-1][k])+1);
			}
		}
	}
	cout<<f[m][n]-1;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
