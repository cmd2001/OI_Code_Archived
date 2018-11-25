#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int m,s=1;scanf("%d",&m);
	for(int i=1;;i++)
	{
		s*=2;
        if(s>m){printf("%d",i);break;}	
	}
	return 0;
}
