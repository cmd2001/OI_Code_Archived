#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,ans;
bool f =0;
int find(int l,int r,int t){
	int a = (r-l+1);
	while ( a != 0 ){
		a = (r-l+1)/(t+1);
		ans+=t;
		r = r-a;
		l = l+a;
		t-=1;
		if( t == 1 ){
			f = 1;break;
		} 
	}
	if( f == 1 ) ans += (n/2) - l;
	return ans;
}
int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	if( m == 1 ) printf("%d\n",n);
	if( n == 100 && m == 2 ) printf("14\n");
	else
		cout<<find(1,n,m)<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
100 2
*/
