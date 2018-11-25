#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
#define debug cout
using namespace std;

int main()
{
	lli a,b;
	cin>>a>>b;
	
	while(a!=b)
	{
		debug<<"a="<<a<<"\nb="<<b<<endl;
		if(a>b) a-=b;
		else b-=a;
	}
	
	cout<<a<<endl;
	
	return 0;
}
