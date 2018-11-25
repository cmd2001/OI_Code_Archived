#include<bits/stdc++.h>
using namespace std;
const int n = 100 , m = 100;

int main()
{
	freopen("dat.txt","w",stdout);
	printf("%d %d\n",n,m);
	for(int t=1;t<=2;t++)
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++)
				printf("%d ",rand()%5000);
			puts("");
		}
	for(int t=1;t<=2;t++)
		for(int i=1;i<n;i++) {
			for(int j=1;j<=m;j++)
				printf("%d ",rand()%5000);
			puts("");
		}
	for(int t=1;t<=2;t++)
		for(int i=1;i<=n;i++) {
			for(int j=1;j<m;j++)
				printf("%d ",rand()%5000);
			puts("");
		}	
}
