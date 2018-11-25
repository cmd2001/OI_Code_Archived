#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

int in[maxn],s[maxn],pos[maxn],n,ans;

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
	n=getint();
	for(int i=1;i<=n;i++)
	{
		in[i]=getint();
		s[i]=in[i]+s[i-1];
		if(s[i]>=n) s[i]%=n;
	}
	for(int i=1;i<=n;i++)
	{
		if(!s[i])
		{
			ans=1;
			printf("%d\n",i);
			for(int j=1;j<=i;j++) printf("%d\n",in[j]);
			break;
		}
	}
	if(!ans)
	{
		int st,ed;
		for(int i=1;i<=n;i++)
		{
			if(pos[s[i]])
			{
				st=pos[s[i]];
				ed=i;
				break;
			}
			pos[s[i]]=i;
		}
		printf("%d\n",ed-st);
		for(int i=st+1;i<=ed;i++) printf("%d\n",in[i]);
	}
	return 0;
}
