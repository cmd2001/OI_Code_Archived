#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

int f[maxn][maxn];

int main()
{
	int n,m;
	cin>>n>>m;
	
	memset(f,0x3f,sizeof(f));
	
	for(int i=0;i<=m;i++) f[0][i]=0;
	
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
		{
			f[i+1][j]=min(f[i+1][j],f[i][j]+1);
			for(int k=1;k<=i;k++) f[i+k][j+1]=min(f[i+k][j+1],f[i][j]+1);
		}
	
	cout<<f[n][m]<<endl;
	
	return 0;
}
