#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

int f[maxn],len,fix;
lli n,k;

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')fix=-1;
		else if(ch==EOF) exit(0);
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	while(n=getint(),k=getint())
	{
		fix=0,len=0;
		memset(f,0,sizeof(f));
		if(n<0&&k>0) fix=1,n=-n;
		while(n) f[++len]=n%k,n/=k;
		if(fix) putchar('-');
		if(k<0)
		{
			lli now=1;
			for(int i=1;i<=len;i++)
			{
				f[i+1]+=f[i]/k;
				f[i]%=-k;
				if(f[i]<0)
				{
					f[i]+=-k,f[i+1]++;
				}
				while(f[len+1]) len++;
			}
		}
		if(!len) putchar('0');
		for(int i=len;i;i--) putchar('0'+f[i]);
		putchar('\n');
	} 
	return 0;
	
}
//371 -10
