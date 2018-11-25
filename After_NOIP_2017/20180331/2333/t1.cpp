#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

lli in[maxn];
int n;

inline bool judge(lli t) {
    __int128 su = 0;
    for(int i=1;i<=n;i++) {
        su += t - in[i];
        if( t < in[i] ) return 0;
    }
    return su >= t;
}
inline lli bin() {
    lli ll = 0 , rr = 1e14 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) ) rr = mid;
        else ll = mid;
    }
    return rr;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",in+i);
    printf("%lld\n",bin());
    return 0;
}
