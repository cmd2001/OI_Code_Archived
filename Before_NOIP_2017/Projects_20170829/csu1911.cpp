#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=524288+1e2;

lli a[maxn],b[maxn];
lli f[maxn];

void fwt(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	fwt(dst,v);
	fwt(dst+v,v);
	for(int i=0;i<v;i++)
		dst[i+v]+=dst[i];
}
void anti_fwt(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	for(int i=0;i<v;i++)
		dst[i+v]-=dst[i];
	anti_fwt(dst,v);
	anti_fwt(dst+v,v);
}

inline int getbin()
{
	int ret=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
		ret=(ret<<1)+(ch-'0'),
		ch=getchar();
	return ret;
}
inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	static int n,m,q,t,len;
	t=getint();
	for(int T=1;T<=t;T++)
	{
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(f,0,sizeof(f));
		
		n=getint(),m=getint();
		len=1<<(m+1);
		
		for(int i=1;i<=n;i++) a[getbin()]++;
		for(int i=1;i<=n;i++) b[getbin()]++;
		
		
		fwt(a,len);
		fwt(b,len);
		for(int i=0;i<len;i++) f[i]=a[i]*b[i];
		anti_fwt(f,len);
		
		q=getint();
		printf("Case #%d:\n",T);
		while(q--)
			printf("%lld\n",f[getbin()]);
	}
	
	return 0;
}

		
	
