#include<cstdio>
typedef long long int lli;

inline lli gcd(lli x,lli y) {
    if( !x || !y ) return x | y;
    register lli t;
    while( t = x % y ) x = y , y = t;
    return y;
}

int main() {
    static lli a,b,x,y;
    scanf("%*d");
    while( scanf("%lld%lld%lld%lld",&a,&b,&x,&y) == 4 ) puts(gcd(a,b)==gcd(x,y)?"Yes":"No");
    return 0;
}
