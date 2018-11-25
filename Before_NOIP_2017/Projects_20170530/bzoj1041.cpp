#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=5e4;
int num[maxn],tme[maxn],cnt;

inline void get_prt(int x)
{
	for(int i=2;i<=x;i++)
	{
		if(!(x%i))
		{
			num[++cnt]=i;
			while(!(x%i)) ++tme[cnt],x/=i;
		}
	}
}

int main()
{
	static int x;
	cin>>x;
	get_prt(x);
	
	return 0;
}
