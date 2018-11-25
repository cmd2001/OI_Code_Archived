#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

int que[maxn],st,ed;
lli in[maxn],sum[maxn],dp[maxn],g[maxn];
int n,l,c;

double getk(int k,int j) // k<j
{
    double y1,y2,dx;
    y1=dp[j]+g[j]*g[j]+2*c*g[j];
    y2=dp[k]+g[k]*g[k]+2*c*g[k];
    dx=2*(g[j]-g[k]);
    return (y1-y2)/dx;
}


int main()
{
    scanf("%d%d",&n,&l);
    c=l+1;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",in+i);
        sum[i]=in[i]+sum[i-1];
        g[i]=sum[i]+i;
    }
    st=1;
    que[++ed]=0;
    for(int i=1,x;i<=n;i++)
    {
        while(st<ed&&getk(que[st],que[st+1])<=g[i]) st++;
        x=que[st];
        dp[i]=dp[x]+(g[i]-g[x]-c)*(g[i]-g[x]-c);
        while(st<ed&&getk(que[ed],i)<getk(que[ed-1],que[ed])) ed--;
        que[++ed]=i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}





