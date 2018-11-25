#include<iostream>
#include<cstdio>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

lli sum[maxn],b[maxn],c[maxn],p[maxn],x[maxn],n;
lli f[maxn];
lli q[maxn],l,r;


inline double gen(int x,int y) // x > y
{
	return (double)(f[x]-f[y]+b[x]-b[y])/(double)(sum[x]-sum[y]);
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
inline void getin()
{
	n=getint();
	for(int i=1;i<=n;i++)
	{
		x[i]=getint(),p[i]=getint(),c[i]=getint();
		sum[i]=sum[i-1]+p[i];
		b[i]=b[i-1]+p[i]*x[i];
	}
}

inline void getans()
{	
	for(int i=1;i<=n;i++)
	{
		while(l<r&&gen(q[l+1],q[l])<x[i]) l++;
		const int pos=q[l];
		f[i]=x[i]*(sum[i]-sum[pos])-(b[i]-b[pos])+c[i]+f[pos];
		while(l<r&&gen(q[r],q[r-1])>gen(i,q[r])) r--;
		q[++r]=i;
	}
}

int main()
{
	getin();
	getans();
	
	printf("%lld\n",f[n]);
	
	return 0;
}
	
