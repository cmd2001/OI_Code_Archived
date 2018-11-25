#include<cstdio>
#include<algorithm>
#define lli long long int
const int maxn=2e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;
 
lli s[maxn],t[maxn],d[maxn];
int n;

inline lli judge(lli x) {
    lli ret = 0;
    for(int i=1;i<=n;i++) if( s[i] <= x ) ret += ( std::min(x,t[i]) - s[i] ) / d[i] + 1ll;
    return ret;
}

inline int bin() {
    lli ll = 0 , rr = inf , mid;
    if( ! ( judge(rr) & 1 ) ) return -1;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) & 1 ) rr = mid;
        else ll = mid;
    }
    return printf("%lld %lld\n",rr,judge(rr)-judge(ll)),1;
}
 
int main() {
    static int T,p;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%lld%lld%lld",s+i,t+i,d+i);
        p = bin();
        if( !~p ) puts("Poor QIN Teng:(");
    }
    return 0;
}
