#include<bits/stdc++.h>
using namespace std;

int _r(int l) {
	return rand()%l+1;
}
int main() {
	srand(time(0));
	freopen("dat.txt","w",stdout);
	const int n = 20 ,m = _r(n);
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",_r(min(n,3)));
	return 0;
}
