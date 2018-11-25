#pragma GCC optimize(2)
#include<cstdio>
const int maxn=35;

int f[maxn];

int main() {
    static int n,ans=0;
    scanf("%d",&n);
    for(register int i=1,t,m;i<=n;i++) {
        scanf("%d",&t) , m = 0;
        for(register int j=0;j<=31;j++)
            if( ( t >> j ) & 1 )
                m = f[j] + 1 > m ? f[j] + 1 : m ;
        for(register int j=0;j<=31;j++)
            if( ( t >> j ) & 1 )
                f[j] = m;
        ans = m > ans ? m : ans;
    }
    printf("%d\n",ans);
    return 0;
}
