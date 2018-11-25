#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long m,mo;
long long now;
long long a[200000];
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	a[0]=1;a[1]=1;
	a[2]=5;a[3]=11;
	now=3;
	while(cin>>m>>mo){
		if(m==0)break;
		if(m<now){
			cout<<a[m]%mo<<endl;
			continue;
		}
		for(int i=now+1;i<=m;i++){
			a[i]=(a[i-1]+5*a[i-2]+a[i-3]-a[i-4])%mo;
		}
		cout<<a[m]%mo<<endl;
		now=m;
	}
	return 0;
}
