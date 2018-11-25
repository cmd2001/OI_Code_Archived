#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;

const int N=5000005;
const int MOD=1000000007;

int tot,prime[N/10];
bool not_prime[N];
LL phi[N];

void get_prime(int n)
{
    phi[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!not_prime[i]) prime[++tot]=i,phi[i]=i-1;
        for (int j=1;j<=tot&&i*prime[j]<=n;j++)
        {
            not_prime[i*prime[j]]=1;
            if (i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
    for (int i=1;i<=n;i++) phi[i]+=phi[i-1];
}

LL solve(int n)
{
    if (n<=5000000) return phi[n];
    LL ans=(LL)n*(n+1)/2;
    //printf("inital = %lld\n",ans);
    for (int i=2,last;i<=n;i=last+1)
    {
        last=n/(n/i);
        ans-=(LL)(last-i+1)*solve(n/i);
    }
    return ans;
}

int main()
{
    get_prime(5000000);
    int n;
    scanf("%d",&n);
    printf("%lld\n",solve(n));
    return 0;
}