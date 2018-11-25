#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
const int base=1e3;

const int dx[]={-1,+1,2,+1,-1,-2};
const int dy[]={-1,-1,0,+1,+1,0};
int x[maxn],y[maxn],cnt;
int num[1010],len,ans;

inline void pre(int mx)
{
	int xx=0,yy=0;
	cnt=1,x[1]=y[1]=0;
	
	for(int len=1;len;len++)
		for(int tar=0;tar<6;tar++) //left-down to correct-left
		{
			int lim=len;
			if(tar==1) lim=len-1;
			for(int i=1;i<=lim;i++)
			{
				x[++cnt]=(xx+=dx[tar]),
				y[cnt]=(yy+=dy[tar]);
				if(cnt==mx) return;
			}
		}
}
inline void multi(int x)
{
	for(int i=1;i<=len;i++)
		num[i]*=x;
	for(int i=1;i<=len;i++)
	{
		num[i+1]+=num[i]/base;
		num[i]%=base;
		while(num[len+1]) len++;
	}
}
inline void divide(int x)
{
	for(int i=len;i;i--)
	{
		num[i-1]+=(num[i]%x)*base;
		num[i]/=x;
	}
	while(!num[len]) len--;
}
inline void calcc(int n,int m)
{
	for(int i=m+1;i<=n;i++) multi(i);
	for(int j=1;j<=(n-m);j++) divide(j);
}
inline void print()
{
	for(int i=len;i;i--)
	{
		if(i==len) printf("%d",num[i]);
		else printf("%03d",num[i]);
	}
	puts("");
}
inline void init()
{
	memset(num,0,sizeof(num));
	num[len=1]=1;
}
inline void getans(int st,int ed)
{
	int dx=abs(x[st]-x[ed]),dy=abs(y[st]-y[ed]);
	if(dx<=dy)
	{
		ans=dy;
		init();
		calcc(dy,(dy-dx)/2); // C(all steps,delta steps)
		printf("%d ",ans);
		print();
	}
	else
	{
		dx-=dy,dx>>=1;
		ans=dx+dy;
		init();
		calcc(dx+dy,min(dx,dy)); // Square Way .
		printf("%d ",ans);
		print();
	}
}

int main()
{
	static int a,b;
	pre(1e6);
	
	while(scanf("%d%d",&a,&b)==2)
	{
		getans(a,b);
	}
	
	//print();
	
	return 0;
}

