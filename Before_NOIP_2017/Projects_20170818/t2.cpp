#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;

lli n,m;

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

inline int getlog(lli x)
{
	int ret=-1;
	while(x)
	{
		ret++;
		x>>=1;
	}
	return ret;
}

lli dfs(lli n,lli m)
{
	debug<<"n="<<n<<"m="<<m<<endl;
	if(!n) return 0;
	int l=getlog(n);
	if(l<m) return l;
	int sq=(double)sqrt(n)+0.5;
	debug<<"sq="<<sq<<endl;
	if(m!=1) return n/sq+dfs(sq,m-1);
	return n-1;
}


int main()
{
	cin>>n>>m;
	debug<<"dfs="<<dfs(n,m)<<endl;
	
	return 0;
}
