#include<bits/stdc++.h>
using namespace std;
const int n=1e4;
int t; 
int main()
{
	freopen("dat.txt","w",stdout);
	while(!(t=rand()%10)) ;
	printf("%d",t);
	for(int i=2;i<=n;i++) printf("%d",rand()%10);
	while(!(t=rand()%10)) ;
	printf("\n%d",t);
	for(int i=2;i<=n;i++) printf("%d",rand()%10);
	printf("\n");
	fclose(stdout);
}
	
