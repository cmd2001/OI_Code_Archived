#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e3+1e2;

int in[maxn],srt[maxn],n,len,ans;
int dp[maxn][maxn];

inline int getint()
{
    int ret=0,fix=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') fix=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')
        ret=ret*10+ch-'0',
        ch=getchar();
    return ret*fix;
}

int main()
{
    n=getint();
    for(int i=1;i<=n;i++) srt[i]=in[i]=getint();
    sort(srt+1,srt+1+n);
    len=unique(srt+1,srt+1+n)-srt-1;

    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        int t=dp[i-1][0];
        for(int j=1;j<=len;j++)
        {
            t=min(t,dp[i-1][j]);
            dp[i][j]=min(dp[i][j],t+abs(in[i]-srt[j]));
        }
    }

    ans=0x7fffffff;
    for(int i=1;i<=len;i++) ans=min(ans,dp[n][i]);

    printf("%d\n",ans);

    return 0;
}
