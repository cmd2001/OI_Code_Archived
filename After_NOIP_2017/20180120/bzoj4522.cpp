#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int lst[15]={0,2,3,5,7,11,13,17,19,23,29,31,61,24251},lstlen=13;
vector<lli> divs;

inline lli mul(lli a,lli b,lli mod) {
    lli ret = 0;
    a %= mod , b %= mod;
    while( b ) {
        if( b & 1 ) ret = ( ret + a ) % mod;
        a = a * 2 % mod , b >>= 1;
    }
    return ret;
}
inline lli fastpow(lli base,lli tme,lli mod) {
    lli ret = 1;
    while( tme ) {
        if( tme & 1 ) ret = mul( ret , base , mod );
        base = mul( base , base , mod );
        tme >>= 1;
    }
    return ret;
}
inline bool test(lli n,lli x) {
    lli p = n - 1 , t = 0;
    while( ! ( p & 1 ) )
        p >>= 1 , ++t;
    p = fastpow(x,p,n);
    if( p == 1 || p == n - 1 ) return 1;
    while( t-- ) {
        p = mul( p , p , n );
        if( p == n - 1 ) return 1;
    }
    return 0;
}
inline bool miller(lli x) {
    for(int i=1;i<=lstlen;i++)
        if( x == lst[i] ) return 1;
    for(int i=1;i<=lstlen;i++)
        if( ! ( x % lst[i] ) ) return 0;
    for(int i=1;i<=lstlen;i++)
        if( !test(x,lst[i]) ) return 0;
    return 1;
}
inline lli rnd(lli p,lli mod) {
    return ( mul( p , p , mod ) + 1 ) % mod;
}
inline lli gcd(lli a,lli b) {
    register lli t;
    while( t = a % b )
        a = b , b = t;
    return b;
}
inline void brute(lli x) {
    lli sq = sqrt(x);
    for(lli i=2;i<=sq;i++)
        if( ! ( x % i ) ) {
            divs.push_back(i);
            while( ! ( x % i ) ) x /= i;
        }
    if( x != 1 ) divs.push_back(x);
}
inline void pollard(lli x) {
    if( miller(x) ) {
        divs.push_back(x);
        return;
    }
    if( x <= 10000000000LL ) {
        brute(x);
        return;
    }
    lli t1 = rnd(rand(),x) , t2 = rnd(t1,x) , g;
    while( 1 ) {
        g = gcd( x , abs(t1-t2) );
        if( g != 1 && g != x ) break;
        t1 = rnd(t1,x) , t2 = rnd(t2,x) , t2 = rnd(t2,x);
        if( t1 == t2 ) {
            t1 = rand() % x + 1 , t2 = rand() % x + 1;
        }
    }
    pollard(g);
    pollard(x/g);
}

int main() {
    static lli e,d,n,c,r,phi,ans;
    
    srand(20010128^20010425);
    
    scanf("%lld%lld%lld",&e,&n,&c);
    
    pollard(n);
    r = 1;
    for(unsigned i=0;i<divs.size();i++)
        r *= divs[i] - 1;
    
    divs.clear();
    pollard(r);
    phi = r;
    sort(divs.begin(),divs.end());
    for(unsigned i=0;i<divs.size();i++)
        if( !i || divs[i] != divs[i-1] )
            phi /= divs[i] , phi *= ( divs[i] - 1 ) ;
    
    d = fastpow(e,phi-1,r);
    
    ans = fastpow(c,d,n);
    
    printf("%lld %lld\n",d,ans);
    
    return 0;
}