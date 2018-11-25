#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
long long k=2,ans;
long long mi(long long k,int n,int m){
	if(n==1) return k;
	if(n%2==0){
		while(n/2){
			k=k*k%m;
			return mi(k,n/2,m);
		}
	}
	else{
		while(n/2){
			int x=k;
			k=k*k%m;
			return mi(k,n/2,m)*x%m;
		}
	}
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d",&n,&m);
	while(n!=0&& m!=0){
		k=2;
		if(n==1) printf("1\n");
		else{
			ans=(mi(2,n,m)+mi(2,n-1,m)-1)%m;
			printf("%d\n",ans);
		}
		scanf("%d%d",&n,&m);
	}
	return 0;
}
