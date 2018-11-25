#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double e = 2.7182818284590452354, pi = 3.141592653589793239;   

inline double calc(int x)
{
	return log10(2*pi*x)/2.0+x*(log10(x/e));
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
	{
		ret=ret*10+ch-'0';
		ch=getchar();
	}
	return ret*fix;
}
int main()
{
	static int t,n,ans;
	t=getint();
	while(t--)
	{
		n=getint();
		ans=calc(n);
		ans++;
		printf("%d\n",ans);
	}
	return 0;
}

