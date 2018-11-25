#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=16;
const lli pw[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000LL,100000000000LL};

lli q(lli base,lli k)
{
	debug<<"base = "<<base<<" k = "<<k<<endl;
	if(k==1) return 1;
	if(!k)
	{
		puts("k == 0 !!! Fuck you !!!");
		return 0;
	}
	if(k>base)
	{
		debug<<"k > base !! unsolvable"<<endl;
		exit(0);
	}
	static lli lam[11][11],mxp[11]; // mxp :: i * (10^mxp) <= base ;
	memset(mxp,0,sizeof(mxp));
	memset(lam,0,sizeof(lam));
	for(lli i=1,tme,p;i<10;i++)
	{
		for(tme=1,p=0;i*tme<=base;tme*=10,p++)
			lam[i][p]=lam[i][p-1]+min(base-i*tme+1,tme);
			mxp[i]=p-1;
	}
	debug<<"output mxp"<<endl;
	for(int i=1;i<10;i++) debug<<mxp[i]<<" ";debug<<endl;
	debug<<"output lam"<<endl;
	for(int i=1;i<10;i++) debug<<lam[i][mxp[i]]<<" ";debug<<endl;
	for(lli i=1;i<10;i++)
	{
		if(k>lam[i][mxp[i]]) k-=lam[i][mxp[i]];
		else
		{
			debug<<"i = "<<i<<"k = "<<k<<endl;
			int j;
			for(j=0;j<=mxp[i];j++)
			{
				if(k<lam[i][j]+1) break;
			}
			k-=lam[i][j-1];
			k--;
			debug<<"new k ="<<k<<"last j = "<<j<<endl;
			debug<<"now + ="<<i*pw[j]<<endl;
			return i*pw[j]+q(pw[j]-1,k);
		}
	}
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

int main()
{
	lli a=getint(),b=getint();
	
	debug<<q(a,b)<<endl;
}
