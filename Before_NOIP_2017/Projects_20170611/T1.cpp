#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e6+1e2,mod=1e9;

int dp[maxn];

int main()
{
    static int n;
    scanf("%d",&n);
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        dp[i]=dp[i-1];
        if(!(i&1)) dp[i]+=dp[i/2];
        if(dp[i]>=mod) dp[i]%=mod;
    }
    printf("%d\n",dp[n]);
    return 0;
}
