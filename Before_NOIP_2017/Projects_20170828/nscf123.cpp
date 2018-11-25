#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=85;

lli bsp[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000LL};

lli f[10][95][95][95]; // len=i , sum=j , mod k = j ;
lli x[10],len;

inline int absmod(long long x,int mod)
{
	long long ret=x%mod;
	if(ret<0) ret+=mod;
	return ret;
}
inline int remmod(long long x,int mod)
{
	x%=mod;
	return (mod-x)%mod;
}

inline void pre()
{
	for(int i=0;i<10;i++)
		for(int j=1;j<=81;j++)
			f[0][i][j][i%j]=1;
	for(int i=1;i<10;i++)
		for(int p=0;p<10;p++)
			for(int j=p;j<=i*9+p;j++)
				for(int k=1;k<90;k++)
					for(int l=0;l<k;l++)
						f[i][j][k][l]+=f[i-1][j-p][k][absmod(l-p*bsp[i],k)];
}
inline lli calc(lli x)
{
	if(x<10) return x;
	lli ret=0,num=0,sum=0,top;
	for(int i=9;i;i--)
	{
		top=(x/bsp[i])%10;
		for(int p=0;p<top;p++)
			for(int j=sum+p?0:1;j<=i*9;j++)
			{
				const int mod=sum+p+j;
				ret+=f[i-1][j][mod][remmod(num+p*bsp[i],mod)];
			}
		sum+=top;
		num+=top*bsp[i];
	}
	top=x%10;
	for(int i=0;i<=top;i++)
		ret+=!((num+i)%(sum+i));
	
	return ret;
}
			
		
	
		
int main()
{
	pre();
	
	int a,b;
	while(scanf("%d%d",&a,&b)==2)
	{
		printf("%lld\n",calc((lli)b)-calc((lli)a-1));
	}
	
	
	return 0;
}
