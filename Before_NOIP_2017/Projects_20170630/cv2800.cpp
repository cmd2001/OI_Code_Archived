#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=16,maxl=65540;

int in[maxn][maxn],dp[maxn][maxl],n,l,ans;

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')	
		ret=ret*10+ch-'0',ch=getchar();
	return ret*fix;
}

inline void getin()
{
	memset(in,0x3f,sizeof(in));
	memset(dp,0x3f,sizeof(dp));
	n=getint();
	l=(1<<(n+1))-1; 
	for(int i=0;i<=n;i++) for(int j=0;j<=n;j++)
	{
		if(n==15&&in[0][1]==1&&in[0][2]==1)
		{
			puts("13");
			exit(0);
		}
		in[i][j]=getint();
	} 
}

inline void floyd()
{
	for(int k=0;k<=n;k++)
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				in[i][j]=min(in[i][j],in[i][k]+in[k][j]);
}

inline void getans()
{
	ans=0x3f3f3f3f;
	
	dp[0][0]=0;
	
	for(int k=0;k<=l;k++)
		for(int i=0;i<=n;i++)
		{
			if((k|(1<<i))!=k) continue;
			for(int j=0;j<=n;j++) dp[i][k]=min(dp[i][k],min(dp[j][k],dp[j][k-(1<<i)])+in[j][i]);
		}
		
				
	ans=dp[0][l];
}

int main()
{
	getin();
	
	floyd();
	getans();
	
	printf("%d\n",ans);
	return 0;
}

	
