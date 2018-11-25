#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e5+1e2;

lli in[maxn];
int n,k;

inline int judge(lli p) {
    int ret = 0;
    lli now = 0;
    for(int i=1;i<=n;i++) {
        now = max( now + in[i] , 0ll );
        if( now >= p )
            ++ret , now = 0;
    }
    return ret;
}

inline lli binmax() {
    lli ll = 0 , rr = 1e18 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) >= k ) ll = mid;
        else rr = mid;
    }
    return ll;
}
inline lli binmin() {
    lli ll = 0 , rr = 1e18 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) <= k ) rr = mid;
        else ll = mid;
    }
    return rr;
}

int main() {
    static lli L,R;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i);
    
    L = binmin() , R = binmax();
    if( judge(L) != k || judge(R) != k ) puts("-1");
    else printf("%lld %lld\n",L,R);
    return 0;
}