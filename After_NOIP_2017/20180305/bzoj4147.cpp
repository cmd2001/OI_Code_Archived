#include<cstdio>
#define lli long long int
using namespace std;

inline lli gcd(lli x,lli y) {
    if( ! ( x && y ) ) return x | y;
    register lli t;
    while( t = x % y )
        x = y , y = t;
    return y;
}

int main() {
    static lli T,p,q,n;
    scanf("%lld",&T);
    while(T--) {
        scanf("%lld%lld%lld",&p,&q,&n);
        if( n % gcd( p , q ) ) {
            puts("R");
            continue;
        }
        if( p == q ) puts("E");
        else if( p > q && n < p ) puts("P");
        else if( p < q && n >= p ) puts("E");
        else if( p > q && n >= p ) {
            if( ! ( n % p ) ) puts("E");
            else if( n % p >= q ) puts("P");
            else if( ! ( n % p % ( p - q ) ) ) puts("E");
            else puts("P");
        } else {
            if( n + p < q ) puts("E");
            else if( n + p == q ) puts("P");
            else if( ! ( n % ( q - p ) ) ) puts("P");
            else puts("E");
        }
    }
    return 0;
}

