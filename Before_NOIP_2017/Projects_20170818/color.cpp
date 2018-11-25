#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define uint unsigned int
#define lli long long int
#define debug cout
using namespace std;
const int maxn=20;

int g[maxn][maxn],app[maxn];
int n,m;
int cnt[maxn];
char s[maxn];

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

uint fastpow(uint tme)
{
	uint ret=1,now=233;
	while(tme)
	{
		if(tme&1) ret*=now;
		now*=now;
		tme>>=1;
	}
	return ret;
}

inline void unzip(uint sta)
{
	memset(app,0,sizeof(app));
	for(uint i=1;i<=n;i++) if(sta&(1<<(i-1))) app[i]=1;
}

inline uint findmx()
{
	memset(cnt,0,sizeof(cnt));
	
	uint ret=0,pos;
	for(int i=1;i<=n;i++)
		if(app[i])
			for(int j=1;j<=n;j++)
				if(app[j]&&g[i][j]) 
					cnt[j]++;
	
	while(1)
	{
		pos=0;
		for(int i=1;i<=n;i++)
			if(app[i]&&cnt[i]>cnt[pos]) pos=i;
		if(!pos) break;
		for(int i=1;i<=n;i++)
			if(app[i]&&g[pos][i]) cnt[i]--,cnt[pos]--;
		++ret;
	}
	return ++ret;
}

inline uint calc(uint sta)
{
	uint ret=1;
	unzip(sta);
	uint f=findmx();
	return f*fastpow(sta);
}


int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	
	static uint ans=0;
	n=getint();
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)
			g[i][j]=s[j]-'0';
	}
	m=(1<<n)-1;
	
	for(uint i=1;i<=m;i++)
		ans+=calc(i);
	
	printf("%u\n",ans);
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
	
	
	


