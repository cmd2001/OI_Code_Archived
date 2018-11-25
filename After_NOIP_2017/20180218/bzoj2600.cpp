#include<cstdio>
#include<algorithm>
#define lli long long int
using std::max;
const int maxn=1e5+1e2;
lli in[maxn],sum[maxn],lim;

inline lli calc(int l,int r) {
    const int mid = ( l + r ) >> 1;
    return sum[r] - sum[mid] - in[mid] * ( r - mid ) - ( sum[mid] - sum[l-1] - in[mid] * ( mid - l + 1 ) ) ;
}
int main() {
    static int n,p,ans;
    scanf("%d%*d%lld",&n,&lim);
    for(int i=1;i<=n;i++) scanf("%lld",in+i) , sum[i] = sum[i-1] + in[i];
    p = 1;
    for(int i=1;i<=n;i++) {
        while( p <= n && calc(i,p) <= lim ) ++p;
        ans = max( ans , p - i );
    }
    printf("%d\n",ans);
    return 0;
}
