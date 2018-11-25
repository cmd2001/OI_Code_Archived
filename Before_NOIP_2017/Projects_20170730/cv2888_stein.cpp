#include<stdio.h>
int n,a,b,t;

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		t=0;
		scanf("%d%d",&a,&b);
		while(1)
		{
			while((!(a&1))&&(!(b&1))) a>>=1,b>>=1,t++;
			while(!(a&1)) a>>=1;
			while(!(b&1)) b>>=1;
			if(a==b) break;
			if(a>b) a-=b;
			else b-=a;
		}
		printf("%d\n",b<<t);
	}
	return 0;
}

