#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m;
int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(m==1){
		printf("%d",n-1);
		return 0;
	}
	if(m==2){
		cout<<(int)((sqrt(8*n+1)-1)/2+0.999);
		return 0;
	}
	if(m>2){
		int cnt=0,l=1,mid=0;
		while(n-mid>1){
			mid=(l+n)/2;
			cnt++;
			l=mid;
		}
		printf("%d",cnt);
		return 0;
	}
	return 0;
}
