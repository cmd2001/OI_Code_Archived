#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;

const int N=55;

LL n,p,k,r;
struct arr{LL f[N];}ans,a;

void mul(arr &a,arr b,arr c)
{
    memset(a.f,0,sizeof(a.f));
    for (int i=0;i<k;i++)
        for (int j=0;j<k;j++)
            a.f[(i+j)%k]=(a.f[(i+j)%k]+b.f[i]*c.f[j]%p)%p;
}

void ksm(arr x,LL y)
{
    y--;
    while (y)
    {
        if (y&1) mul(ans,ans,x);
        mul(x,x,x);y>>=1;
    }
}

int main()
{
	freopen("data.in","r",stdin);
	freopen("std.out","w",stdout);
    scanf("%lld%lld%lld%lld",&n,&p,&k,&r);
    a.f[0]++;a.f[1%k]++;ans=a;
    ksm(a,n*k);
    printf("%lld",ans.f[r]);
    return 0;
}
