#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1048580;
int in[maxn],n,c,t;
lli tar[maxn];

void fwt_and(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	fwt_and(dst,v);
	fwt_and(dst+v,v);
	for(int i=0;i<v;i++)
		dst[i]+=dst[i+v];

}
void anti_fwt_and(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	for(int i=0;i<v;i++)
		dst[i]-=dst[i+v];
	anti_fwt_and(dst,v);
	anti_fwt_and(dst+v,v);
}
void fwt_or(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	fwt_or(dst,v);
	fwt_or(dst+v,v);
	for(int i=0;i<v;i++)
		dst[i+v]+=dst[i];
}
void anti_fwt_or(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	for(int i=0;i<v;i++)
		dst[i+v]-=dst[i];
	anti_fwt_or(dst,v);
	anti_fwt_or(dst+v,v);
}
void fwt_xor(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	fwt_xor(dst,v);
	fwt_xor(dst+v,v);
	for(int i=0;i<v;i++)
	{
		const lli x=dst[i],y=dst[i+v];
		dst[i]=x+y;
		dst[i+v]=x-y;
	}
}
void anti_fwt_xor(lli* dst,int len)
{
	if(len==1) return;
	int v=len>>1;
	
	for(int i=0;i<v;i++)
	{
		const lli x=dst[i],y=dst[i+v];
		dst[i]=(x+y)>>1;
		dst[i+v]=(x-y)>>1;
	}
	anti_fwt_xor(dst,v);
	anti_fwt_xor(dst+v,v);
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}
inline void getin()
{
	n=getint(),c=getint();
	for(int i=1;i<=n;i++) in[i]=getint();
}
inline int getlen(int x)
{
	int ret=0;
	while(x) ret++,x>>=1;
	return 1<<ret;
}
inline void calc_case()
{
	int ans=0,len=0;
	memset(tar,0,sizeof(tar));
	
	getin();
	
	for(int i=1;i<=n;i++) tar[in[i]]++,len=max(len,in[i]);
	
	len=getlen(len);
	

	if(c==1)
	{
		fwt_and(tar,len);
		for(int i=0;i<len;i++) tar[i]*=tar[i];
		anti_fwt_and(tar,len);
		for(int i=1;i<=n;i++) tar[in[i]]--;
	}
	else if(c==2)
	{
		fwt_xor(tar,len);
		for(int i=0;i<len;i++)
			tar[i]*=tar[i];
		anti_fwt_xor(tar,len);
	}
	else if(c==3)
	{
		fwt_or(tar,len);
		for(int i=0;i<len;i++) tar[i]*=tar[i];
		anti_fwt_or(tar,len);
	}
	for(int i=len-1;i>=0;i--)
		if(tar[i])
		{
			ans=i;
			break;
		}
	printf("%d\n",ans);
}

int main()
{
	for(int t=getint();t;t--)
		calc_case();
	return 0;
}
	
	


