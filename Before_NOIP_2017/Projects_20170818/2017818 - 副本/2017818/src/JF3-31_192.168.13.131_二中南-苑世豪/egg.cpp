#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define maxn 1010
const int INF=0x3f3f3f3f;
int n,m;
int f[maxn][maxn];

int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)f[i][1]=i;
	for(int i=1;i<=m;i++)f[1][i]=1;
	for(int i=2;i<=n;i++){
		for(int j=2;j<=m;j++){
			f[i][j]=max(f[i-1][j],f[i-1][j-1])+1;
			if(f[i-1][j]!=0&&f[i-2][j]>f[i-2][j-1])f[i][j]=min(f[i][j],f[i-1][j]);
		}
	}
	cout<<f[n][m]<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
