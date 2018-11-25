#include<bits/stdc++.h>
using namespace std;

inline int _rand(int l) {
	return rand() % l + 1;
}
int main() {
	srand(time(0));
	freopen("dat.txt","w",stdout);
	const int n = 100000 , m = 500000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d%c",rand()-rand(),i!=n?' ':'\n');
	for(int i=1,sta,pos,kk,tt;i<=m;i++) {
		tt = i * 10 + _rand(10);
		//tt = 10;
		sta = _rand(2);
		if( i <= ( m >> 1 )  )
			tt = 0 , sta = 1;
		if( sta == 1 ) {
			pos = _rand(n) , kk = rand() - rand();
			printf("%d c %d %d\n",tt,pos,kk);
		}
		else
			printf("%d q\n",tt);
	}
	return 0;
}
