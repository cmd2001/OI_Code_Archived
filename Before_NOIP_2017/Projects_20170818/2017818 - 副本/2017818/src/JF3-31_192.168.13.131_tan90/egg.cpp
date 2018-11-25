#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int N,M;
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&N,&M);
	if(M==1) printf("%d",N);
	else printf("%d",N/2);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
