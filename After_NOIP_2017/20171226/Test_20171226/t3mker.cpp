#include<bits/stdc++.h>
using namespace std;

inline int _rand(int r) {
	return ( rand() % r ) + 1;
}

int main() {
	srand(time(NULL));
	int n = 5 , x = _rand(10), y = _rand(10), z = _rand(10);
	printf("%d %d %d %d\n",n,x,y,z);
	for(int i=1;i<=n;i++)
		printf("%d %d %d\n",_rand(x),_rand(y),_rand(z));
	return 0;
}
