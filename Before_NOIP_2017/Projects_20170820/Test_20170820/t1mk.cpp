#include<bits/stdc++.h>
#define lli long long int
using namespace std;

inline int gen(int x)
{
	int ret=0;
	for(int i=1;i<=x;i++)
		if(!(x%i)) ret++;
	return ret;
}
inline int calc(lli x)
{
	int ret=0;
	lli sq=sqrt(x);
	
	for(int i=1;i<=sq;i++)
		if(!(x%i)) ret+=2;
	
	if(sq*sq==x) --ret;
	
	return ret;
}


int main()
{
	int x;
	cin>>x;
	
	cout<<gen(x)<<endl;
	
	return 0;
}
