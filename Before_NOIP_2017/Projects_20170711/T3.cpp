#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxl=260;

lli in[maxn][maxn];
lli dp[2][maxn][maxn];
lli a[maxl],len,n,m;
int cur=1;

inline lli sq(lli x)
{
    return x*x;
}
inline void init()
{
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dp[cur][i][j]=sq(in[i][j]-a[1]);
}
inline lli update(int i,int j,int cur)
{
    return min(min(dp[cur][i+1][j],dp[cur][i-1][j]),min(dp[cur][i][j+1],dp[cur][i][j-1]));
}
inline void calc()
{
    for(int l=2;l<=len;l++)
    {
        debug<<"l="<<l-1<<endl;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++) debug<<dp[cur][i][j]<<" ";
            debug<<endl;
        }
        cur^=1;
        memset(dp[cur],0x3f,sizeof(dp[1]));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                dp[cur][i][j]=update(i,j,cur^1)+sq(in[i][j]-a[l]);
    }
}


inline void getin()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%lld",&in[i][j]);
    scanf("%lld",&len);
    for(int i=1;i<=len;i++) scanf("%lld",a+i);
}
int main()
{
    getin();
    init();
    calc();
    lli ans=0x3f3f3f3f;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ans=min(ans,dp[cur][i][j]);
    debug<<"ans="<<ans<<endl;
    return 0;
}
