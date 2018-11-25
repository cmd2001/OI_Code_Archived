#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;
#define Mod 1000000007
#define LL long long
#define N 10000005

int n,k=1000000;
int prime[N],p[N],mu[N];
LL ans,sum[N];

void get()
{
    mu[1]=1;
    for (int i=2;i<=k;++i)
    {
        if (!p[i])
        {
            prime[++prime[0]]=i;
            mu[i]=-1;
        }
        for (int j=1;j<=prime[0]&&i*prime[j]<=k;++j)
        {
            p[i*prime[j]]=1;
            if (i%prime[j]==0)
            {
                mu[i*prime[j]]=0;
                break;
            }
            else mu[i*prime[j]]=-mu[i];
        }
    }
    for (int i=1;i<=k;++i) mu[i]+=mu[i-1];
}
LL getmu(int x)
{
    if (x<=k) return mu[x];
    return sum[n/x];
}
void summu()
{
    int t;
    for (t=1;n/t>k;++t);
    //printf("t = %d\n",t);
    for (;t;--t)
    {
        int m=n/t;
        sum[t]=1;
        for (int i=2,j=0;i<=m;i=j+1)
        {
            j=m/(m/i);
            sum[t]-=getmu(m/i)*(LL)(j-i+1);
            sum[t]%=Mod;
        }
    }
}
LL f(int n)
{
    LL ans=0;
    for (int i=1,j=0;i<=n;i=j+1)
    {
        j=n/(n/i);
        ans+=(LL)(j-i+1)*(n/i)%Mod;
        ans%=Mod;
    }
    return ans*ans%Mod;
}
int main()
{
    scanf("%d",&n);
    get();summu();
    for (int i=1,j=0;i<=n;i=j+1)
    {
        j=n/(n/i);
        ans+=f(n/i)*(getmu(j)-getmu(i-1))%Mod;
        ans%=Mod;
    }
    ans=(ans+Mod)%Mod;
    printf("%lld\n",ans);
}
