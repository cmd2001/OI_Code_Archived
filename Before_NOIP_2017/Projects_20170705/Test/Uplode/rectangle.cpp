#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
const int mod=95041567;
//Just a hopeless violent solution of T3

int c[maxn][maxn];
lli bell[maxn],n;

inline void getc(int n) //generate c[x][y] from 0 to n 
{
	register int t;	
	for(int i=1;i<=n;i++) c[i][0]=c[i][i]=1;
	
	for(int i=2;i<=n;i++)
	{
		for(int k=1;k<n;k++)
		{
			t=c[i-1][k-1]+c[i-1][k];
			if(t>=mod) t%=mod;
			c[i][k]=t;
		}
	}
}
inline void getbell(int n) //generate bell number from 0 to n
{
	bell[0]=1,bell[1]=1;
	register lli t;
	for(int i=1;i<n;i++)
	{
		t=0;
		for(int k=0;k<=i;k++)
		{
			t+=c[i][k]*bell[k];
			if(t>=mod) t%=mod;
		}
		bell[i+1]=t;
	}
}

int main()
{
	freopen("rectangle.in","r",stdin);
	freopen("rectangle.out","w",stdout);
	
	static int t,in[15],maxin=0;
	scanf("%d",&t);
	for(int i=1;i<=t;i++) scanf("%d",in+i),maxin=max(maxin,in[i]);
	if(maxin>1100) return 0; // I'm a good juruo who doesn't stuck the tester!!! 
	
	getc(maxin);
	getbell(maxin);
	
	for(int i=1;i<=t;i++) printf("%lld\n",bell[in[i]]);
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
		
