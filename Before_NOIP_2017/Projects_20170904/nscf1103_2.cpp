#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=16;
const lli pw[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000LL,100000000000LL};

lli nums[maxn],len;
lli m,k,now,pr;

lli pre(lli x)
{
	lli ret=0,now=0;
	while(x) nums[++len]=x%10,x/=10;
	for(int i=len;i;i--)
		now=now*10+nums[i],
		ret+=now-pw[len-i]+1;
	return ret;
}
		

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

bool judge(lli x)
{
	while(x!=1)
	{
		if(x%10) return 0;
		x/=10;
	}
	return 1;
}

int main()
{
	m=getint(),k=getint();
	
	pr=pre(m);
	if(k<pr) return puts("0");
	else if(k==pr) printf("%lld\n",m);
	else if(judge(m)) return puts("0");
	else
	{
		k=k-pr;
		now=1;
		while(now*10<=m) now*=10;
		while(1)
		{
			m*=10,now*=10;
			if(k>=m-now) k-=(m-now);
			else
			{
				printf("%lld\n",now+k-1);
				return 0;
			}
		}
	}
	
	return 0;
}
