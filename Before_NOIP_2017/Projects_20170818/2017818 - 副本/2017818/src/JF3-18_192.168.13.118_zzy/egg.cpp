#include<cstdio>
#include<iostream>
using namespace std;
const int maxn = 1010;
int n , m;
int f[maxn][maxn];
int main(){
	freopen("egg.in" , "r" , stdin);
	freopen("egg.out" , "w" , stdout);
	scanf("%d%d" , &n , &m);
	for(int i = 1;i <= n;i ++)
	{
		for(int j = 0;j <= m;j ++)
		{
			f[i][j] = i;
		}
	}
	for(int i = 1;i <= n;i ++)
	{
		for(int k = 1;k <= i;k ++)
		{
			for(int j = 2;j <= m;j ++)
			{
				f[i][j] = min(f[i][j] , max(f[k - 1][j - 1] , f[i - k][j]) + 1);
			}
		}
	}
	printf("%d" , f[n][m]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
