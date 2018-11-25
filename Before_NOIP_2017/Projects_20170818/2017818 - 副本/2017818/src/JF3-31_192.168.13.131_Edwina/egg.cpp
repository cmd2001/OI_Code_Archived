#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int f[1001][1001];
int n,m;
inline void Edwina()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
}
int main()
{
	Edwina();
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)
			for(int j=0;j<=m;j++)
				f[i][j]=i;
		for(int i=1;i<=n;i++)
			for(int k=1;k<=i;k++)
				for(int j=2;j<=m;j++)
					f[i][j]=min(f[i][j],max(f[k-1][j-1],f[i-k][j])+1);
		cout<<f[n][m]<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

