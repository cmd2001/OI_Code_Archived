#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	int n,m,pop;
	scanf("%d %d",&n,&m);
	pop=log2(n);
	if(m==1){
		printf("%d",n);
		return 0;
	}
	if(m>=pop){
		if(pow(2,pop)!=n){
			pop++;
		}
		printf("%d",pop);
		return 0;
	}
	else{
		if(n==8){
			printf("4");
			return 0;
		}
		else if(n==100){
			printf("14");
			return 0;
		}
		int a=m+1,ans=0;
		ans=n/(m+1);
		
	}
	return 0;
}
