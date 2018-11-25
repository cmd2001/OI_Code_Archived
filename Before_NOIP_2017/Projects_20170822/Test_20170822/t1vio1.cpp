#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=5e3+1e2;

int f[maxn],n,p;

int main()
{
	cin>>n>>p;
	f[1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++) f[i]+=f[j]*(n-i),f[i]%=p;
		//debug<<f[i]<<endl;
	}
	
	
	cout<<f[n-1]<<endl;
	
	return 0;
}
