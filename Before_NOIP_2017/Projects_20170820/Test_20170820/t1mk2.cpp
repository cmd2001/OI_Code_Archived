#include<bits/stdc++.h>
#include<cmath>
using namespace std;
const int maxn=1e2+1e1;

int t[maxn],cnt;

inline bool isprime(int x)
{
	for(int i=2;i<=sqrt(x);i++)
		if(x%i==0) return 0;
	return 1;
}

int main()
{
	long long int ans=1;
	for(int i=1;ans<=2000000000;i++)
	{
		if(isprime(i))
		{
			ans*=i;
			t[++cnt]=ans;
			printf("Multied %d = %lld\n",i,ans);
		}
	}
	for(int i=1;i<=cnt;i++) printf("%d,",t[i]);	
	return 0;
}
