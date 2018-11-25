#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=85;

lli bsp[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000LL};

lli f[10][82][82][82]; // len=i , sum=j , mod k = j ;
lli x[10],len;

inline int absmod(int x,int mod)
{
	int ret=x%mod;
	ret+=ret<0?mod:0;
	return ret;
}

inline void getf()
{
	for(int k=1;k<=81;k++) // k is the target mod .
	{
		f[0][0][k][0]=1;
		for(int i=1;i<10;i++) // i is the length
			for(int j=1;j<=81;j++) // j is the sum of bits;
				for(int l=1;l<=81;l++) // l is the remainer .
					for(int p=0;p<10;p++)
						if(j-p>=0) f[i][j][k][l]+=f[i-1][j-p][k][absmod(l-p*bsp[i-1],k)];
	}
		
}

lli dfs(lli dep)
{
	int ret=0;
}

inline void cut(lli arg)
{
	memset(x,0,sizeof(x));
	len=0;
	while(arg) x[++len]=arg%10,arg/=10;
}

int main()
{
	getf();
	return 0;
}
