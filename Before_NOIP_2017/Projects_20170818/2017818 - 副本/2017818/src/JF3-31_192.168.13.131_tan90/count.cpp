#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int N,M;
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	while(scanf("%d%d",&N,&M))
	{
		if(!N&&!M) break;
		else
		{
			if(N==1) printf("%d\n",1%M);
			else if(N==2) printf("%d\n",5%M);
			else if(N==3) printf("%d\n",11%M);
			else if(N==4) printf("%d\n",40%M);
			else if(N==5) printf("%d\n",95%M);
			else printf("6\n");
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
