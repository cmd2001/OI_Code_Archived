#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstring>
//#define debug cout
using namespace std;
const int maxn=3e7+1e2;

short int tmp[35];
short int bit[maxn];
int n,q,a,b,cnt,tn;

inline void convert(unsigned tar)
{
	memset(tmp,0,sizeof(tmp));
	cnt=0;
	while(tar)
	{
		tmp[++cnt]=tar&1;
		tar>>=1;
	}
}
inline void update(int pos,int ope)
{
	for(int i=pos,j=1;j<=cnt;i++,j++) bit[i]+=ope*tmp[j];
	for(int i=pos;i<=tn;i++)
	{
		if(bit[i]<0) bit[i]+=2,bit[i+1]--;
		else if(bit[i]>1) bit[i+1]++,bit[i]-=2;
		else if(i-pos>32) break;
	}
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
	
int main()
{
	freopen("integer.in","r",stdin);
	freopen("integer.out","w",stdout);
	static unsigned int k;
	n=getint();
	getint(),tn=getint(),getint();
	if(tn==1) tn=30;
	else if(tn==2) tn=100;
	else if(tn==3) tn=n;
	else if(tn==4) tn=30*n;
	for(int i=1;i<=n;i++)
	{
		q=getint(),a=getint();
		if(q==2)
		{
			printf("%d\n",(int)bit[a]);
		}
		else
		{
			b=getint();
			k=abs(a);
			convert(k);
			if(a>0) update(b,1);
			else update(b,-1);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
