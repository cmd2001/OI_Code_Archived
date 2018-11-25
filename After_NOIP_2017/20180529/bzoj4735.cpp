#include<cstdio>
const int mod=998244353;

int main() {
    static int n,m,ans=1;
    scanf("%d",&n);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , m += t;
    for(int i=1;i<=m;i++) if( i != m - n + 1 ) ans = (long long) ans * i % mod;
    printf("%lld\n",ans);
    return 0;
}
