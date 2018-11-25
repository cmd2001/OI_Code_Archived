#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const lli inf = 0x3f3f3f3f3f3f3f3fll;

lli t[maxn],e[maxn];
int n,m;
lli c,a,b;

inline lli calc(lli d) {
    lli ret = 0 , more = 0 , less = 0;
    for(int i=1;i<=n;i++)
        ret += max( d - t[i] , 0ll ) * c;
    if( a < b ) {
        for(int i=1;i<=m;i++)
            more += max( d - e[i] , 0ll ) ,
            less += max( e[i] - d , 0ll );
        if( less <= more ) ret += less * a;
        else ret += more * a + ( less - more ) * b;
    } else {
        for(int i=1;i<=m;i++)
            less += max( e[i] - d , 0ll );
        ret += less * b;
    }
    return ret;
}
inline lli bin(lli l,lli r) {;
    lli ret = inf , mid1 , mid2 , c1 , c2;
    while( r > l + 2 ) {
        mid1 =  ( 2 * l + r  ) / 3  , mid2 = ( l + 2 * r ) / 3;
        c1 = calc(mid1) , c2 = calc(mid2);
        if( c1 == c2 ) l = mid1 , r = mid2;
        else if( c1 > c2 ) l = mid1;
        else r = mid2;
    }
    for(lli i=l;i<=r;i++)
        ret = min( ret , calc(i) );
    return ret;
}
inline lli judge() {
    lli mi = inf;
    for(int i=1;i<=n;i++)
        mi = min( mi , t[i] );
    return calc(mi);
}

int main() {
    scanf("%lld%lld%lld",&a,&b,&c);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld",t+i);
    for(int i=1;i<=m;i++)
        scanf("%lld",e+i);
    if( c == 1e16 )
        printf("%lld\n",judge());
    else printf("%lld\n",bin(1,1e5+1));
    return 0;
}
