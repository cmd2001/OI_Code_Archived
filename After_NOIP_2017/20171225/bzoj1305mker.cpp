#include<bits/stdc++.h>
using namespace std;

int _r(int l) {
	return rand()%l+1;
}

int main() {
	freopen("dat.txt","w",stdout);
	int n=50,k=_r(n>>2);
	cout<<n<<" "<<k<<endl;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++)
			putchar(_r(2)==1?'Y':'N');
		putchar('\n');
	}
	return fclose(stdout);
}
