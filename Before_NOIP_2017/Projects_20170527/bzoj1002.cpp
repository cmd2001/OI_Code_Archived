#include<bits/stdc++.h>
using namespace std;
const int maxn=110;
struct bignum
{
	int dat[maxn],len;
	friend bignum operator * (const bignum &a,const int &b)
	{
		bignum ret=a;
		for(int i=1;i<=a.len;i++) ret.dat[i]*=b;
		for(int i=1;i<=a.len;i++) ret.dat[i+1]+=ret.dat[i]/10,ret.dat[i]%=10;
		if(ret.dat[ret.len+1]) ret.len++;
		return ret;
	}
	friend bignum operator - (const bignum &a,const bignum &b)
	{
		bignum ret=a;
		int len=b.len;
		for(int i=1;i<=len;i++)
		{
			ret.dat[i]-=b.dat[i];
			if(ret.dat[i]<0) ret.dat[i]+=10,ret.dat[i+1]--;
		}
		while(!ret.dat[ret.len]) ret.len--;
		return ret;
	}
	friend bignum operator + (const bignum &a,const int &b)
	{
		bignum ret=a;
		ret.dat[1]+=b;
		for(int i=1;i<=ret.len;i++) ret.dat[i+1]+=ret.dat[i]/10,ret.dat[i]%=10;
		if(ret.dat[ret.len+1]) ret.len++;
		return ret;
	}
}f[110];
int main()
{
	int n;
	f[1].dat[1]=f[2].len=f[1].len=1;
	f[2].dat[1]=5;
	scanf("%d",&n);
	for(int i=3;i<=n;i++) f[i]=(f[i-1]*3-f[i-2]+2);
	for(int i=f[n].len;i>0;i--) putchar(f[n].dat[i]+'0');
	putchar('\n');
	return 0;
}
	

