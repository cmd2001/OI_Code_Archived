#include<bits/stdc++.h>
#define lli long long int
using namespace std;

int ans;
const int mod=1e9+7;

void dfs(int st,int ed,bool tar)
{
	bool uns=1;
	if(tar==1)
	{
		for(int i=st+1;i<ed;i++)
		{
			uns=0;
			dfs(st,i,0);
		}
	}
	else
	{
		for(int i=st+1;i<ed;i++)
		{
			uns=0;
			dfs(i,ed,1);
		}
	}
	if(uns) ++ans;
}

inline lli fastpow(lli base,lli tme,lli mod)
{
	lli ret=1,now=base%mod;
	while(tme)
	{
		if(tme&1) ret=ret*now%mod;
		now=now*now%mod;
		tme>>=1;
	}
	return ret;
}

int main()
{
	long long int n;
	cin>>n;
	
	//cout<<"n-2="<<n-2<<endl;
	
	//dfs(1,n+1,1);
	
	cout << fastpow(2,n-2,mod) << endl;
	//cout<<ans<<endl;
	return 0;
}
