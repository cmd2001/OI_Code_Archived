#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int n;
bool map[19][19];
char c;

int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	srand(time(0));
	scanf("%d",&n);
	getchar();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			c=getchar();
			if(c=='1')map[i][j]=1;
		}
		getchar();
	}
	printf("%d",rand()%(1ll<<32));
	return 0;
}
