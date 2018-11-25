// by spli
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;

int n,m;
LL f[1010][1010];

int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	if(m==1){
		cout<<n-1;return 0;
	}
	if(m==2){
		LL s=0;
		for(int i=1;i<=n;++i){
			s+=i;
			if(s>=n){
				cout<<i;
				return 0;
			}
		}
	}
	else{
		for(int i=1;i<=m;++i) f[m+1][i]=1;
		for(int i=2*m+1;i<=n;i+=m+1)
			for(int j=1;j<=m;++j) f[i][j]=f[i-1][j]+1;
		int k=n-n%(m+1);
		cout<<f[k][1]+n%(m+1);
	}
	return 0;
}


















