//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxd=20,MOD=1000000000;
int dp[maxn][maxd],n,d;
int main()
{
    freopen("time.in","r",stdin);
    freopen("time.out","w",stdout);
    scanf("%d",&n);
    while(n>(1<<d)) d++;
    for(int i=1;i<=n;i++) dp[i][0]=1;
    for(int i=1;i<=d;i++) dp[1<<i][i]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=d;j++)
        {
            dp[i][j]=((long long)dp[i][j]+dp[i][j-1])%MOD;
            if(i-(1<<j)>0) dp[i][j]=((long long)dp[i-(1<<j)][j]+dp[i][j])%MOD;
        }
    }
    printf("%d\n",dp[n][d]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
