#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int f[1010][1010];
int main(){
	//freopen("in.txt","r",stdin);
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	memset(f,0x3f3f3f3f,sizeof(f));
	for(int i=0;i<=n;i++) f[1][i]=i;
	for(int i=0;i<=m;i++) f[i][0]=0;
	for(int i=2;i<=m;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=j;k++) f[i][j]=min(f[i][j],max(f[i-1][k-1],f[i][j-k])+1);
	/*for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) cout<<f[i][j]<<" ";
		cout<<endl;
	}*/
		
	printf("%d\n",f[m][n]);
}

