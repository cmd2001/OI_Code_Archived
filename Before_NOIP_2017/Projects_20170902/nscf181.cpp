#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxm=2e4+1e2;

int f[maxm],n,tar;
int val[maxn],tme[maxn];
int used[maxn][maxm];
int ans[maxn];

inline void getans()
{
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1,t;i<=n;i++)
	{
		for(t=1;t<=tme[i];tme[i]-=t,t*=2)
			for(int j=tar;j-t*val[i]>=0;j--)
				if(f[j]>f[j-t*val[i]]+t)
				{
					f[j]=f[j-t*val[i]]+t;
					used[i][j]=used[i][j-t*val[i]]+t;
				}
		t=tme[i];
		for(int j=tar;j-t*val[i]>=0;j--)
			if(f[j]>f[j-t*val[i]]+t)
			{
				f[j]=f[j-t*val[i]]+t;
				used[i][j]=used[i][j-t*val[i]]+t;
			}
		//for(int i=1;i<=tar;i++) debug<<f[i]<<" ";debug<<endl;
	}
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	n=getint();
	for(int i=1;i<=n;i++) val[i]=getint();
	for(int i=1;i<=n;i++) tme[i]=getint();
	tar=getint();
	
	getans();
	
	printf("%d\n",f[tar]);
	
	for(int i=n,lst=tar;i;i--)
	{
		ans[i]=used[i][lst];
		lst-=val[i]*used[i][lst];
	}
	
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	
	putchar('\n');
	
	
	return 0;
}
	
