#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxl=65;

int in[maxl],n,b,m,ans=-1;
bool dp[2][maxn];
int cur=0;

int main()
{
    scanf("%d%d%d",&n,&b,&m);
    dp[cur][b]=1;

    for(int i=1;i<n;i++) scanf("%d",in+i);

    for(int i=1;i<n;i++)
    {
        cur^=1;
        memset(dp[cur],0,sizeof(dp[1]));
        for(int k=0;k<=m;k++)
        {
            if(dp[cur^1][k])
            {
                if(k+in[i]<=m) dp[cur][k+in[i]]=1;
                if(k-in[i]>=0) dp[cur][k-in[i]]=1;
            }
        }
    }

    for(int i=0;i<=m;i++) if(dp[cur][i]) ans=max(ans,i);

    debug<<"ans="<<ans<<endl;

    return 0;
}


