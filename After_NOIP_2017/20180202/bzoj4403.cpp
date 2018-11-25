#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int mod=1e6+3;

lli fac[mod+2],inv[mod+2];

inline lli getinv(lli base) {
    lli ret = 1;
    int tme = mod - 2;
    while( tme ) {
        if( tme & 1 ) ret = ret * base % mod;
        base = base * base % mod;
        tme >>= 1;
    }
    return ret;
}
inline void gen() {
    *fac = 1;
    for(int i=1;i<mod;i++)
        fac[i] = fac[i-1] * i % mod;
    inv[mod-1] = getinv(fac[mod-1]);
    for(int i=mod-2;~i;i--)
        inv[i] = inv[i+1] * ( i + 1 ) % mod;
}
inline lli c(lli n,lli m) {
    if( n < m ) return 0;
    return fac[n] * inv[m] % mod * inv[n-m] % mod;
}

inline lli lucas(lli n,lli m) {
    if( n < mod && m < mod ) return c( n , m );
    return lucas( n / mod , m / mod ) * lucas( n % mod , m % mod );
}

int main() {
    static int t,l,r,n;
    static lli ans;
    gen();
    scanf("%d",&t);
    while( t-- ) {
        scanf("%d%d%d",&n,&l,&r);
        ans = lucas( r - l + n + 1 , n ) - 1;
        ans = ( ans + mod ) % mod;
        printf("%lld\n",ans);
    }
    return 0;
}

