#include<cstdio>
using namespace std;

int n;

int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		if(n<3) puts("Alice");
		else puts("Bob");
	}
	
	return 0;
}
