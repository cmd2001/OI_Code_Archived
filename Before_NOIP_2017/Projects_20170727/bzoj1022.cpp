#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
	static int t,n,in,nim,flag;
	
	scanf("%d",&t);
	while(t--)
	{
		nim=0,flag=0;
		scanf("%d",&n);
		while(n--)
		{
			scanf("%d",&in);
			nim^=in;
			if(in!=1) flag=1;
		}
		if((flag&&nim)||((!flag)&&(!nim))) puts("John");
		else puts("Brother");
	}
	return 0;
}
	
