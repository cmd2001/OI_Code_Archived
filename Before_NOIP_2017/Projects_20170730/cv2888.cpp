#include<stdio.h>
int n,a,b,t;

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&a,&b);
		while(t=a%b)
		{
			a=b;
			b=t;
		}
		printf("%d\n",b);
	}
	return 0;
}
