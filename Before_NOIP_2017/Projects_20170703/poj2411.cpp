#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=25,mod=100003;

int dp[maxn][2150],n,m,maxx,ans;
bool used[maxn],nextrow[maxn];

inline void unzip(int x)
{
	memset(used,0,sizeof(used));
	for(int i=1;i<=n;i++)
		if(x&(1<<(i-1))) used[i]=1;
}

inline int zip()
{
	int ret=0;
	for(int i=1;i<=n;i++)
		if(nextrow[i]) ret|=(1<<(i-1));
	return ret;
}

void dfs(int pos,int now,int i)
{
	if(pos==n)
	{
		if(used[pos])
		{

			dp[i+1][zip()]+=now;
			//dp[i+1][zip()]%=mod;
			return;
		}
		else
		{
			nextrow[pos]=1;
			dp[i+1][zip()]+=now;
			//dp[i+1][zip()]%=mod;
			nextrow[pos]=0;
			return;
		}
	}

	if(used[pos]) dfs(pos+1,now,i);
	else
	{
		used[pos]=1;

		nextrow[pos]=1;
		dfs(pos+1,now,i);
		nextrow[pos]=0;

		if(!used[pos+1])
		{
			used[pos+1]=1;
			dfs(pos+1,now,i);
			used[pos+1]=0;
		}

		used[pos]=0;
	}
}
int main()
{
    //freopen("dat.in","r",stdin);
	while(scanf("%d%d",&n,&m)==2&&(n||m))
    {
        memset(dp,0,sizeof(dp));
        maxx=(1<<(n))-1;
        dp[0][0]=1;
        for(int i=0;i<=m;i++)
            for(int j=0;j<=maxx;j++)
            {
                unzip(j);
                dfs(1,dp[i][j],i);
            }
        ans=dp[m][0];
        printf("%d\n",ans);
    }
	return 0;
}
