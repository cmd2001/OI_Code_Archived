#include<cstdio>
using namespace std;
const int maxn=5e6+1e2;

int prime[maxn],chain[maxn],cnt;
bool vis[maxn];

inline void gen(int lim)
{
	for(int i=2,j;i<=lim;i++)
	{
		if(!vis[i]) prime[++cnt]=i,chain[i]=cnt;
		for(j=1;j<=cnt&&i*prime[j]<=lim&&i%prime[j];j++) vis[i*prime[j]]=1,chain[i*prime[j]]=j;
		if(i*prime[j]<=lim) vis[i*prime[j]]=1,chain[i*prime[j]]=j;
	}
}

inline long long div(register int &x)
{
	long long ret=0;
	while(x!=1)
	{
		ret+=prime[chain[x]];
		x/=prime[chain[x]];
	}
	return ret;
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
	gen(5e6);
	
	register int in;
	
	while(in=getint()) printf("%lld\n",div(in));
	
	return 0;
}
