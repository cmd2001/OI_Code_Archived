#include<stdio.h>

int n,k;

int main()
{
	scanf("%d%d",&n,&k);
	printf("%d\n",n==1?1:(k>n-k+1?n-k+1:k)<<1);
	return 0;
}
	
