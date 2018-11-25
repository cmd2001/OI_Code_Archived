#include<bits/stdc++.h>
using namespace std;
long long n,m,f[1200][1200];
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	cin>>n>>m;
	if(n==0)
	{
		cout<<0<<endl;
		return 0;
	}
	memset(f,11,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		f[i][1]=i;
	}
	for(int i=1;i<=m;i++)
	{
		f[1][m]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=1;k<=i;k++)
			{
				f[i][j]=min(f[i][j],max(f[k][j-1],f[i-k][j]+1));
			}
		}
	}
	cout<<f[n][m];
}
