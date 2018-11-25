#include<iostream>
#include<cstdio>
#include<cstring>
#define lli long long int
#define debug cout
using namespace std;
const int maxd=512;

lli dp[2][100][maxd],ans;
int cnt[maxd]; 
int n,k,ms,cur;

inline int div(int x)
{
	#define lowbit(x) (x&(-x))
	int ret=0;
	while(x)
	{
		ret++;
		x-=lowbit(x);
	}
	return ret;
}
inline void getcnt()
{
	for(int i=0;i<ms;i++) cnt[i]=div(i);
}

int main()
{
	scanf("%d%d",&n,&k);
	
	ms=1<<n;
	
	getcnt();
	
	for(int i=0;i<ms;i++) if((!(i&(i<<1)))&&(!(i&(i>>1))))
	{
		//debug<<"i="<<i<<"cnt="<<cnt[i]<<endl;
		dp[cur][cnt[i]][i]=1;
	}
	
	for(int i=1;i<n;i++)
	{
		memset(dp[cur^1],0,sizeof(dp[1]));
		for(int sta=0;sta<ms;sta++)
			for(int siz=0;siz<=k;siz++)
			{
				if(dp[cur][siz][sta])
					for(int nxt=0;nxt<ms;nxt++)
						if((!(nxt&(nxt<<1)))&&(!(nxt&(nxt>>1))))
						{
							if((!(sta&nxt))&&(!(sta&(nxt<<1)))&&(!(sta&(nxt>>1))))
							{
								dp[cur^1][siz+cnt[nxt]][nxt]+=dp[cur][siz][sta];
							}
						}
			}
						
		cur^=1;
	}
	
	for(int i=0;i<ms;i++) ans+=dp[cur][k][i];
	
	//debug<<"ans="<<ans<<endl;
	
	printf("%lld\n",ans);
	
	return 0;
}
		
