#include<cstdio>
#define lli long long int

inline lli gcd(lli a,lli b) {
    if( ! ( a && b ) ) return a | b;
    register lli t;
    while( t = a % b )
        a = b , b = t;
    return b;
}
inline bool judge(lli x,lli y,lli g) {
    return  ! ( x % g ) && ! ( y % g ) ;
}

int main() {
    static int T;
    static lli a,b,x,y,g;
    scanf("%d",&T);
    while( T-- ) {
        scanf("%lld%lld%lld%lld",&a,&b,&x,&y);
        g = gcd( a , b ) << 1;
        if( !g ) puts( ( !x && !y ) ? "Y" : "N" );
        if( judge( x + a , y + b , g ) || judge( x + b , y + a , g ) || judge( x + a + b , y + a + b , g) || judge( x , y , g ) ) puts("Y");
        else puts("N");
    }
    return 0;
}
