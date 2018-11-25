#include<bits/stdc++.h>
using namespace std;

int main() {
	long long ret = 0;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) {
			ret += i * j * __gcd(i,j);
			/*if( __gcd(i,j) == 1 )
				cout<<"g == 1 ans + = "<<i * j * __gcd(i,j)<<endl;
			if( __gcd(i,j) == 2 )
				cout<<"g == 2 ans + = "<<i * j * __gcd(i,j)<<endl;*/
		}
	cout<<ret<<endl;
}
