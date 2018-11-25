#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+ch-'0',
		ch=getchar();
	return ret*fix;
}

int n;
lli a,b,c;
bool isa,isb,isc;
bool aebb,becb,ceab;
bool aebl,becl,ceal;
bool can;
int main()
{
	while(n=getint())
	{
		isa=isb=isc=0;
		aebb=becb=ceab=0;
		aebl=becl=ceal=0;
		can=0;
		for(int i=1;i<=n;i++)
		{
			a=getint(),b=getint(),c=getint();
			if(a==b&&b==c&&a) can=1;
			if(a>b&&a>c) isa=1;
			if(b>a&&b>c) isb=1;
			if(c>a&&c>b) isc=1;
			if(a==b)
			{
				if(a>c) aebb=1;
				else if(a<c) aebl=1;
			}
			if(b==c)
			{
				if(b>a) becb=1;
				else if(b<a) becl=1;
			}
			if(c==a)
			{
				if(c>b) ceab=1;
				else if(c<b) ceal=1;
			}
		}
		if(can||(isa&&isb&&isc)||(aebb&&aebl)||(becb&&becl)||(ceab&&ceal)) puts("uspekh");
		else puts("otkaz");
	}
	
	return 0;
}
		


