#include<bits/stdc++.h>
#define debug cout
using namespace std;
long long int a[1005][1005],b[1005][1005];
long long int c[1005][1005];
long long int ai,aj,bi,bj;
int main()
{
    scanf("%lld%lld",&ai,&aj);
    for(long long int i=1;i<=ai;i++) for(long long int j=1;j<=aj;j++) scanf("%lld",&a[i][j]);
    scanf("%lld%lld",&bi,&bj);
    for(long long int i=1;i<=bi;i++) for(long long int j=1;j<=bj;j++) scanf("%lld",&b[i][j]);
    for(long long int i=1;i<=ai;i++)
    {
        for(long long int j=1;j<=bj;j++)
        {
            for(long long int k=1;k<=aj;k++) c[i][j]+=a[i][k]*b[k][j];
            printf("%lld ",c[i][j]);
        }
        printf("\n");
    }
    return 0;
}

