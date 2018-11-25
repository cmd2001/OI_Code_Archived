#include<cstdio>
#define lli long long int

lli n,m,p;

inline lli mul(lli a,lli b) {
    lli ret = 0;
    while( b ) {
        if( b & 1 ) ret = ( ret + a ) % p;
        if( b >>= 1 ) a = ( a + a ) % p; 
    }
    return ret;
}
inline lli fastpow(lli base,lli tim) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret % p;
}

int main() {
    scanf("%lld%lld%lld",&n,&m,&p);
    printf("%lld\n",mul(fastpow(n,m-1),fastpow(m,n-1)));
    return 0;
}
