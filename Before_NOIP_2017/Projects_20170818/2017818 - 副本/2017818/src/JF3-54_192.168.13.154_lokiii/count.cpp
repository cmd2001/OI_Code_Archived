#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
long long dp[2][100005],cur,m,n;
long long work(int n)
{
    memset(dp[0],0,sizeof(dp[0]));
    dp[cur=0][16-1]=1;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=4;j++)
    {
        cur^=1;
        memset(dp[cur],0,sizeof(dp[cur]));
        int r=16-1;
        for(int k=0;k<16;k++)
        {
            long long v=dp[cur^1][k];
            if((k&(1<<4-1))==0)//Êú
            dp[cur][(k<<1)+1]=(dp[cur][(k<<1)+1]+v)%m;
            else
            {
                dp[cur][(k<<1)&r]=(dp[cur][(k<<1)&r]+v)%m;//²»·Å
                if(j>1&&(k&1)==0)//ºá
                dp[cur][((k<<1)+3)&r]=(dp[cur][((k<<1)+3)&r]+v)%m;
			}
        }
    }
    return dp[cur][16-1];
}
int main()
{
    freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
    while(scanf("%d%d",&n,&m)&&n+m)
    printf("%lld\n",work(n));
    return 0;
}
