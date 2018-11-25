#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define lli long long int
using namespace std;
const int maxn=1e3+1e2;

lli f[maxn][maxn],ans;
int n,d;

int main()
{
	cin>>n;
	
	d=ceil(sqrt(double(n)));
	
	f[0][0]=1;
	
	for(int i=0;i<=n;i++)
		for(int j=0;j<=d;j++)
			for(int k=j;k<=d;k++)
				if(k&&i+k*k<=n) f[i+k*k][k]+=f[i][j];
	
	for(int i=1;i<=d;i++) ans+=f[n][i];
	
	cout<<ans<<endl;
	
	return 0;
}

