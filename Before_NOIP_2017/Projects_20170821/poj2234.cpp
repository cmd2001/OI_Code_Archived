#include<cstdio>
using namespace std;

int main()
{
	static int n,k,x;
	
	while(scanf("%d",&n)==1)
	{
		k=x=0;
		while(n--)
			scanf("%d",&k),x^=k;
		
		if(x) puts("Yes");
		else puts("No");
	}
	
	return 0;
}
