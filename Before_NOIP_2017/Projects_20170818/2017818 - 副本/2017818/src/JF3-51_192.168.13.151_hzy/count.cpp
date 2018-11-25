#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 9000;
int n,m;
long long int a[maxn];
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	memset(a,0,sizeof(a));
	a[0] = a[1] = 1;
	a[2] = 5;
	a[3] = 11;
	for(int i=4;i<=maxn;i++){
		a[i] = a[i-1] + (5*a[i-2]) + a[i-3] - a[i-4];
	}
	while(scanf("%d%d",&n,&m)){
		if( n == 0 && m == 0 ) break;
		else{
			int ans = a[n] % m ;
			printf("%d\n",ans);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
1 10000
3 10000
5 10000
0 0
*/
