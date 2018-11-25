#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e1+5e0;
//Just a hopeless violent simulaton solution of T2.

int str[maxn],exp[maxn],h[maxn],n,way,cnt;
int color[maxn];
int sum[maxn];
lli incr[maxn];
bool g[maxn][maxn];
lli ans;

inline void dfs(int pos,int col)
{
	for(int i=1;i<=n;i++)
	{
		if(g[pos][i]&&!color[i])
		{
			color[i]=col;
			dfs(i,col);
		}
	}
}
inline void recolor()
{
	memset(color,0,sizeof(color));
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(!color[i])
		{
			color[i]=++cnt;
			dfs(i,cnt);
		}
	}
	/*debug<<"color="<<endl;
	for(int i=1;i<=n;i++) debug<<color[i]<<" ";
	debug<<endl;*/
}

inline void merge() // merge block cnt into block cnt-1
{
	int miv,pos1,pos2,f,t;
	miv=0x3f3f3f3f;
	for(int i=1;i<=n;i++) // i is the city of cnt
		for(int j=1;j<=n;j++) // j is the city of cnt-1
		{
			if(color[i]!=color[j])
			{
				f=(exp[i]-str[i])*h[j]+(exp[j]-str[j])*h[i];
				if(f<miv) miv=f,pos1=i,pos2=j;
			}
		}
	debug<<"connected pos1="<<pos1<<"	pos2="<<pos2<<endl;
	g[pos1][pos2]=g[pos2][pos1]=1;
	ans+=way;
	t=color[pos1];
	for(int i=1;i<=n;i++) if(color[i]==t) color[i]=color[pos2];
}
inline void connect()
{
	recolor();
	while(cnt!=1)
	{
		merge();
		recolor();
	}

}

inline void getsum()
{
	for(int i=1;i<=n;i++)
	{
		sum[i]=str[i];
		for(int k=1;k<=n;k++) if(g[i][k]) sum[i]+=str[k];
	}
}
inline void getincr()
{
	for(int i=1;i<=n;i++)
	{
		incr[i]=0;
		for(int k=1;k<=n;k++)
		{
			if(g[i][k]&&i!=k&&str[k]!=exp[k]) incr[i]+=h[k]*(exp[k]-str[k]);
		}
		if(str[i]<exp[i]-1) incr[i]+=h[i];
	}
}
inline void updateincr(int pos)
{
	if(str[pos]!=exp[pos]) return;
	for(int i=1;i<=n;i++)
	{
		if(g[pos][i]) incr[i]-=h[pos];
	}
}
inline void updatesum(int pos)
{
	sum[pos]++;
	for(int i=1;i<=n;i++)
	{
		if(g[pos][i]) sum[i]++;
	}
}
inline void build()
{
	int delta=0,pos;
	lli mi=0x3f3f3f3f;
	lli t;
	for(int i=1;i<=n;i++) delta+=(exp[i]-str[i]);
	getsum();
	getincr();
	for(int i=1;i<=delta;i++)
	{
		mi=0x3f3f3f3f;
		for(int k=1;k<=n;k++) if(str[k]!=exp[k]&&incr[k]<mi)
		{
			pos=k;
			mi=incr[k];
		}
		debug<<"building pos="<<pos<<endl;
		debug<<"sum="<<sum[pos]<<endl;
		ans+=(lli)sum[pos]*h[pos];
		debug<<"+="<<sum[pos]*h[pos]<<endl;
		str[pos]++;
		updateincr(pos);
		debug<<"updateing sum"<<endl;
		debug<<"sum1="<<sum[pos]<<endl;
		updatesum(pos);
		debug<<"sum2="<<sum[pos]<<endl;
	}
}
	
	
inline void getin()
{
	static char tmp[60];
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",str+i);
	for(int i=1;i<=n;i++) scanf("%d",exp+i);
	for(int i=1;i<=n;i++) scanf("%d",h+i);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",tmp+1);
		for(int j=1;j<=n;j++) if(*(tmp+j)=='Y') g[i][j]=1;
	}
	for(int i=1;i<=n;i++) g[i][i]=0;
	scanf("%d",&way);
}

int main()
{
	getin();
	connect();
	debug<<"after connecy ans="<<ans<<endl;
	build();
	debug<<"after build ans="<<ans<<endl;
	
	return 0;
}
