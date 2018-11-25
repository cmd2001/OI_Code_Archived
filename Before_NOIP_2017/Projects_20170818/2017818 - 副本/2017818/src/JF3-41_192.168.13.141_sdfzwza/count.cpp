#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
long long m;
long long f[100010][6];
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	while(scanf("%d%lld",&n,&m)){
		if(!n&&!m) return 0;
		memset(f,0,sizeof(f));
		f[1][0]=f[1][1]=f[1][2]=f[1][3]=f[1][4]=f[1][5]=1;
		for(int i=2;i<=n;i++){
			f[i][0]=f[i-1][4]%m;
			f[i][1]=(f[i-1][4]+f[i-1][3])%m;
			f[i][2]=(f[i-1][4]+f[i-2][2])%m;
			f[i][3]=(f[i-1][4]+f[i-1][1])%m;
			f[i][4]=(f[i-1][0]+f[i-1][1]+f[i-1][2]+f[i-1][3]+f[i-1][4])%m;
			/*f[i][0]=(f[i-1][0]+f[i-1][1]+f[i-1][3]+f[i-1][4]+f[i-1][5])%m;
			f[i][1]=(f[i-1][0]+f[i-1][4])%m;
			f[i][2]=(f[i-1][3])%m;
			f[i][3]=(f[i-1][0]+f[i-1][2])%m;
			f[i][4]=(f[i-1][0]+f[i-1][1])%m;
			f[i][5]=(f[i-1][0])%m;*/
		}
		printf("%lld\n",f[n][4]);
	}
}

