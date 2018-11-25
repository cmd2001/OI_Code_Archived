#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;


lli p;

inline lli fastpow(lli base,lli tme,lli p) {
    lli ret = 1;
    while( tme ) {
        if( tme & 1 ) ret = ret * base % p;
        base = base * base % p;
        tme >>= 1;
    }
    return ret % p;
}
inline lli inv(lli y,lli z) {
    if( ! ( y % p ) ) return -1;
    return z * fastpow(y,p-2,p) % p;
}
inline lli bsgs(lli y,lli z) {
    if( ( ! ( y % p ) ) && ( z % p ) ) return -1;
    map<lli,lli> mp;
    lli sq = ( sqrt(p) + 0.5 );
    
    lli inv = fastpow(y,p-2,p) , now = 1 , per;
    for(int i=0;i<sq;i++) {
        if( !mp.count(now) ) mp[now] = i;
        now = now * inv % p;
    }
    now = fastpow(z,p-2,p) , per = fastpow(y,sq,p);
    for(int i=0;i<=sq;i++) {
        if( mp.count(now) ) return i * sq + mp[now];
        now = now * per % p;
    }
    
    return -1;
}

int main() {
    static int t,k;
    static lli y,z,ans;
    while( scanf("%d%d",&t,&k) == 2 ) {
        while( t-- ) {
            scanf("%lld%lld%lld",&y,&z,&p);
            if( k == 1 ) ans = fastpow(y,z,p);
            else if( k == 2 ) ans = inv(y,z);
            else if( k == 3 ) ans = bsgs(y,z);
            if( !~ans ) puts("Orz, I cannot find x!");
            else printf("%lld\n",ans);
        }
    }
    
    return 0;
}