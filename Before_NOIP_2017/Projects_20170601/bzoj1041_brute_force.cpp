#include<bits/stdc++.h>
using namespace std;
int main()
{
	static long long int in,sq,cnt=0;
	cin>>in;
	cnt=0;
	sq=in*in;
	for(long long int i=1,x;i<=in;i++)
	{
		x=sqrt(sq-i*i);
		if(x*x==sq-i*i)
		{
			cout<<"x="<<x<<endl;
			++cnt;
		}
	}
	printf("%lld %lld\n",in,4*cnt);
	return 0;
}
