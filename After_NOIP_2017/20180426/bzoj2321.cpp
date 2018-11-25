#include<cstdio>
typedef long long int lli;

int main() {
    static int n,m,t;
    static lli ans;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&t) , ans += ( i * i + j * j ) * t;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&t) , ans -= ( i * i + j * j ) * t;
    printf("%lld\n",ans>>1);
    return 0;
}
