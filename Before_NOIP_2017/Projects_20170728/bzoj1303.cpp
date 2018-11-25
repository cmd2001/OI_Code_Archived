#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],n,p,pos;
int dat[maxn<<1],sum[maxn<<1];
lli ans;

inline void ope(int pos)
{
	dat[pos+maxn]++;
}
inline int query(int pos)
{
	return dat[pos+maxn];
}

int main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&in[i]);
		if(in[i]==p) in[i]=0,pos=i;
		else if(in[i]<p) in[i]=-1;
		else if(in[i]>p) in[i]=1;
		else puts("Fuck you!");
	}
	for(int i=pos;i<=n;i++)
	{
		sum[i]=sum[i-1]+in[i];
		//debug<<"i="<<i<<"sum="<<sum[i]<<endl;
		ope(sum[i]);
	}
	for(int i=pos;i;i--)
	{
		sum[i-1]=sum[i]+in[i-1];
		ans+=query(-sum[i]);
	}
	
	
	printf("%lld\n",ans);
	
	return 0;
}
		
		
	
