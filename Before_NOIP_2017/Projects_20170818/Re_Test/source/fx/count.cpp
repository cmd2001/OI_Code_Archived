#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=20;

int n,mod;
struct martix
{
	lli dat[maxn][maxn];
	martix(int f=0)
	{
		memset(dat,0,sizeof(dat));
		if(f) for(int i=0;i<16;i++) dat[i][i]=1;
	}
	lli* operator [] (const int &x)
	{
		return dat[x];
	}
	inline void in(int base[16][16])
	{
		for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				dat[i][j]=base[i][j];
	}
	friend martix operator * (martix &a,martix &b)
	{
		martix ret;
		for(int i=0;i<16;i++)
			for(int j=0;j<16;j++)
				for(int k=0;k<16;k++)
					ret[i][j]+=a[i][k]*b[k][j],ret[i][j]%=mod;
		return ret;
	}
	inline void print()
	{
		for(int i=0;i<16;i++)
		{
			for(int j=0;j<16;j++) printf("%d ",dat[i][j]);
			puts("");
		}
	}
}base,st,mid,ed;

martix fastpow(martix base,int tme)
{
	martix ret=martix(1);
	while(tme)
	{
		if(tme&1) ret=ret*base;
		base=base*base;
		tme>>=1;
	}
	return ret;
}
int b[16][16]=
{
{1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1},
{0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int main()
{
	base.in(b);
	st[0][0]=1;
	while(scanf("%d%d",&n,&mod)==2&&(n||mod))
	{
		mid=fastpow(base,n);
		ed=st*mid;
		printf("%lld\n",ed[0][0]);
	}
	return 0;
}
