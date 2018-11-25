#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
int n,m;
string s[3]={"Open","Close","Ask"};
int main()
{
	freopen("dat.txt","w",stdout);
	srand(time(0));
	n=5,m=200;
	printf("%d\n",n);
	for(int i=1;i<=m;i++)
	{
		int type=rand()%3,type2=rand()%2,a,b,c,d;
		if( i <= n * 4 )
			type = 0;
		if(type==2)a=rand()%2+1,b=rand()%n+1,c=rand()%2+1,d=rand()%n+1;
		else a=rand()%2+1,b=rand()%n+1,c=type2?(((a-1)^1)+1):a,d=type2?b:(b+rand()%2*2-1);
		if(d==0)d=2;
		if(d==n+1)d=n-1;
		if( a==c && b==d ) {
			--i;
			continue;
		}
		printf("%s %d %d %d %d\n",s[type].c_str(),a,b,c,d);
	}
	printf("Exit\n");
	return 0;
}
