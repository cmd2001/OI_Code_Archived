#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3;

inline long long int c(int a,int b)
{
	if(b==0||a==b) return 1;
	__int128 x=1,y=1;
	for(int i=1;i<=a;i++) x*=i;
	for(int i=1;i<=b;i++) y*=i;
	for(int i=1;i<=a-b;i++) y*=i;
	return (long long int)(x/y);
}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int s=0;
		for(int k=0;k<=n;k++) s+=c(i,k);
		cout<<s<<endl;
	}
	return 0;
}
