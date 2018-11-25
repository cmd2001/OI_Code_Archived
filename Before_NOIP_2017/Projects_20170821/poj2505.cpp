#include<cstdio>
#define lli long long int
using namespace std;
lli n,t;

int main()
{
	while(scanf("%lld",&n)==1)
	{
		t=0;
		
		while(n!=1)
		{
			if(t&1) n=(n+1)>>1;
			else n=(n+8)/9;
			t++;
		}
		
		puts((t&1)?"Stan wins.":"Ollie wins.");
	}
	
	return 0;
}

