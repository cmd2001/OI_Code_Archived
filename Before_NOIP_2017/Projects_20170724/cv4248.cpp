#include<iostream>
#include<cstdio>
#include<cmath>
#define ulli unsigned long long int
#define debuf cout
using namespace std;

ulli i,n,tmp,ans;

int main()
{
	static int t;
	cin>>t;
	while(t--)
	{
		ans=1;
		cin>>n;
		tmp=n;
		for(i=2;i*i*i<=tmp;i++)
		{
			if(!(tmp%i))
			{
				while(!(tmp%i)) tmp/=i;
				ans*=i;
			}
		}
		if(tmp>1)
		{
			if(floor(sqrt(tmp))==sqrt(tmp)) ans*=floor(sqrt(tmp));
			else ans*=tmp;
		}
		cout<<n-ans<<endl;
	}
	return 0;
}

