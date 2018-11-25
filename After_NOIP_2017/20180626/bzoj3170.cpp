#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long int lli;
const int maxn=1e5+1e2;
const lli inf = 0x3f3f3f3f3f3f3f3fll;

lli xsrt[maxn],ysrt[maxn],xsu[maxn],ysu[maxn],x[maxn],y[maxn],ans = inf;

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,a,b;i<=n;i++) scanf("%d%d",&a,&b) , xsrt[i] = x[i] = a + b , ysrt[i] = y[i] = a - b;
    sort(xsrt+1,xsrt+1+n) , sort(ysrt+1,ysrt+1+n);
    for(int i=1;i<=n;i++) xsu[i] = xsu[i-1] + xsrt[i] , ysu[i] = ysu[i-1] + ysrt[i];
    for(int i=1;i<=n;i++) {
        const int xp = lower_bound(xsrt+1,xsrt+1+n,x[i]) - xsrt , yp = lower_bound(ysrt+1,ysrt+1+n,y[i]) - ysrt;
        ans = min( ans , xp * x[i] - xsu[xp] + ( xsu[n] - xsu[xp] ) - ( n - xp ) * x[i] + yp * y[i] - ysu[yp] + ( ysu[n] - ysu[yp] ) - ( n - yp ) * y[i] );
    }
    printf("%lld\n",ans>>1);
    return 0;
}
