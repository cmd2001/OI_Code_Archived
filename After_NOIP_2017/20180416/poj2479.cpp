#include<cstdio>
#include<algorithm>
const int maxn=5e4+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],pr[maxn],su[maxn],prf[maxn],suf[maxn];

int main() {
    static int T,n,ans,mi;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n) , pr[0] = su[n+1] = 0 , ans = prf[0] = suf[n+1] = -inf;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        for(int i=1;i<=n;i++) pr[i] = pr[i-1] + in[i];
        for(int i=n;i>=1;i--) su[i] = su[i+1] + in[i];
        mi = 0; for(int i=1;i<=n;i++) prf[i] = std::max( prf[i-1] , pr[i] - mi ) , mi = std::min( mi , pr[i] );
        mi = 0; for(int i=n;i>=1;i--) suf[i] = std::max( suf[i+1] , su[i] - mi ) , mi = std::min( mi , su[i] );
        for(int i=1;i<n;i++) ans = std::max( ans , prf[i] + suf[i+1] );
        printf("%d\n",ans);
    }
    return 0;
}
