#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+1e2,maxl=1600100 ;

int dev[maxl],n,k,cnt;

inline void calc(int x)
{
	int sq=sqrt(x);
	for(int i=1;i<sq;i++)
	{
		if(!(x%i))
		{
			dev[++cnt]=i;
			dev[++cnt]=x/i;
		}
	}
	if(sq*sq==x) dev[++cnt]=sq;
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
	n=getint(),k=getint();
	for(register int i=1,t;i<=n;i++)
	{
		t=getint();
		calc(t);
	}
	
	sort(dev+1,dev+1+cnt);
	
	for(int i=cnt,c;i;i--)
	{
		if(dev[i]==dev[i+1]) c++;
		else c=1;
		if(c>=k)
		{
			printf("%d\n",dev[i]);
			break;
		}
	}
	return 0;
	
}
