#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=3e3+1e2;

lli f[maxn][maxn],ans;
int n,d;

int main()
{
    scanf("%d",&n);
    d=ceil(sqrt((double)n));

    f[0][0]=1;
    for(lli i=0;i<=n;i++)
        for(lli j=0;j<=d;j++)
            for(lli k=j;k<=d;k++)
            {
                if(k&&i+k*k<=n) f[i+k*k][k]+=f[i][j];
            }
    for(int i=d;i;i--) ans+=f[n][i];

    printf("%lld\n",ans);

    return 0;
}
