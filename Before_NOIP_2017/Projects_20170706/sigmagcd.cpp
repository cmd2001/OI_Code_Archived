#include<bits/stdc++.h>
using namespace std;

inline int gcd(int a,int b)
{
	while(a%b)
	{
		a%=b;
		a^=b^=a^=b;
	}
	return b;
}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cout<<gcd(i,n)<<endl;
	return 0;
}
