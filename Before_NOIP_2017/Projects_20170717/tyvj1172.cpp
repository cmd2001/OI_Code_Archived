#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=4e3+1e2;

int n;
unsigned int f[maxn];

int main()
{
	scanf("%d",&n);
	
	f[0]=1;
	for(int i=1;i<n;i++)
		for(int j=i;j<=n;j++)
			f[j]+=f[j-i],f[j]%=2147483648LL;
			
	cout<<f[n]<<endl;
	
	return 0;
}
