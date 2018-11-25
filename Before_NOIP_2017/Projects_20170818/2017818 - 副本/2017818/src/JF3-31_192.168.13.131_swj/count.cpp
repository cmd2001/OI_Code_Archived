#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m;
long long f[100010];
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	f[1]=1;
	f[2]=5;
	f[3]=11;
	f[4]=36;
	for(int i=5;i<=100000;++i){
		f[i]=f[i-1]+5*f[i-2]+f[i-3]-f[i-4];
	}
	while(cin>>n>>m){
		if(n==0&&m==0) break;
		cout<<f[n]%m<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
