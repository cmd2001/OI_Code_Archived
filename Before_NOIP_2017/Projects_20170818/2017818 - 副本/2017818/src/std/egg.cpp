#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int f[1005][15];
int n,m;
int main(){// <--注意不要换行
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout); 
	scanf("%d%d",&n,&m);
	int mx=log2(n)+2;
	m = min(m,mx);
	memset(f,0x3f,sizeof f);
	for(int i=0;i<=m;i++) f[0][i]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=i;k++){
				f[i][j]=min(f[i][j],1+max(f[k-1][j-1],f[i-k][j]));
			}
		}
	}
	printf("%d\n",f[n][m]);
	fclose(stdout);
	return 0;
}