#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#define ll long long
using namespace std;
ll f[2][(1<<10)];
ll n,m,p,tmp;
ll read()
{
	
	ll x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
ll cal(int m)
{
	f[tmp=0][(1<<m)-1]=1;
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=m;j++)
		{
			tmp^=1;
			memset(f[tmp],0,sizeof(f[tmp]));
			ll r=(1<<m)-1;
			for(int s=0;s<(1<<m);s++)
			{
				ll v=f[tmp^1][s];
				if((s&(1<<m-1))==0)
				{
					f[tmp][(s<<1)+1]+=v;
					f[tmp][(s<<1)+1]%=p;
				}
				else
				{
					f[tmp][(s<<1)&r]+=v;
					f[tmp][(s<<1)&r]%=p;
					if(j>1&&(s&1)==0)
					{
						f[tmp][((s<<1)+3)&r]+=v%p;
						f[tmp][((s<<1)+3)&r]%=p;
					}
				}
			}
		}
	}
	return f[tmp][(1<<m)-1]%p;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	n=read();
	p=read();
	printf("%lld\n",cal(n));
	return 0;
}
