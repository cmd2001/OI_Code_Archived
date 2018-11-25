#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

lli in[maxn],n,k,m;
int tar[64][maxn]; // Do not swap i,j besause it may cause TLE

inline lli getint()
{
	lli ret=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret;
}

inline void gen()
{
	int s=1,e=k+1;
	for(int i=1;i<=n;i++)
	{
		while(e<n && in[i]-in[s] > in[e+1]-in[i]) s++,e++;
		tar[0][i]=s;
		if(in[e]-in[i] > in[i]-in[s]) tar[0][i]=e;
	}
}
inline void pre()
{
	for(int i=1;i<64;i++)
		for(int j=1;j<=n;j++)
			tar[i][j]=tar[i-1][tar[i-1][j]];
}
inline int query(int pos)
{
	int ret=pos;
	for(int i=0;i<63;i++)
		if((1LL<<i)&m) ret=tar[i][ret];
	return ret;
}

int main()
{
	
	n=getint(),k=getint(),m=getint();
	for(int i=1;i<=n;i++) in[i]=getint();
	
	sort(in+1,in+1+n);
	
	gen();
	//for(int i=1;i<=n;i++) debug<<tar[i][0]<<" ";debug<<endl;
	pre();
	
	for(int i=1;i<=n;i++) printf("%d ",query(i));
	
	putchar('\n');
	
	
	return 0;
}
	
