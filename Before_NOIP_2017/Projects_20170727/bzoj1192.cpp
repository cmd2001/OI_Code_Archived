#include<iostream>
#include<cstdio>
using namespace std;

int in,ans;

int main()
{
	scanf("%d",&in);
	while(in)
	{
		in>>=1;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
 
