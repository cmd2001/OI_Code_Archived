#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int inf=20000;
int n,m;
int f[1010][1010];
int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		f[i][1]=i;
		for(int j=2;j<=m;++j){
			f[i][j]=inf;
			for(int k=1;k<=i;++k){
				f[i][j]=min(f[i][j],1+max(f[k-1][j-1],f[i-k][j]));
			}
		}
	}
	cout<<f[n][m];
	fclose(stdin);
	fclose(stdout);
	return 0;
}
