#include<bits/stdc++.h>
using namespace std;


int main() {
	freopen("dat.txt","w",stdout);
	const int n = 1e3;
	cout<<n<<endl;
	for(int i=1;i<=n;i++) {
		printf("%0.2lf %0.2lf\n",((double)rand())/rand(),((double)rand())/rand());
	}
	return 0;
}
