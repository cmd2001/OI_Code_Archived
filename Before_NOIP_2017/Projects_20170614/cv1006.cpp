#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1;

int in[maxn],n,len,out;
int delta[maxn*maxn],dp[maxn],ans[maxn];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);

    sort(in+1,in+1+n);
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) delta[++len]=in[j]-in[i];

    len=unique(delta+1,delta+1+len)-delta;

    for(int i=1;i<=len;i++)
    {
        ans[i]=1;
        for(int j=1;j<=n;j++) dp[j]=1;
        for(int j=1;j<=n;j++)
        {
            for(int k=j-1;k>0;k--)
            {
                if(in[j]-in[k]==delta[i]) ans[i]=max(ans[i],dp[j]=max(dp[j],dp[k]+1));
            }
        }
    }

    for(int i=1;i<=len;i++) out=max(out,ans[i]);

    printf("%d\n",out);

    return 0;
}

