#include<cstdio>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<cstring>
using namespace std;
int main()
{
	srand(time(0));
	int i,n,m,h;
	printf("1\n100000 5\n");
	for(i=1;i<=100000;i++)
	{
		n=rand()%100000+1;
		printf("%d ",n);
	}
	printf("\n");
	for(i=1;i<=100000;i++)
	{
		n=rand()%100000+1;
		m=rand()%100000+1;
		while(n>m)
		{
			n=rand()%100000+1;
			m=rand()%100000+1;
		}
		h=rand()%100000;
		printf("%d %d %d\n",n-1,m-1,h);
	}
	return 0;
}
