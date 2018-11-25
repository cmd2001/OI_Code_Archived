#include<cstdio>
#define lli long long int
const int mod=9999991;


int main() {
    static int n;
    static lli ans = 1;
    scanf("%d",&n);
    for(int i=1;i<=n-2;i++)
        ans = ans * n % mod;
    for(int i=1;i<=n-1;i++)
        ans = ans * i % mod;
    printf("%lld\n",ans);
    return 0;
}
