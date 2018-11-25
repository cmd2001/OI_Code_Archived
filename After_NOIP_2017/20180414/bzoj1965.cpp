#include<cstdio>
typedef unsigned long long int ulli;

ulli n,m,l,mod;

inline ulli mul(ulli x,ulli y) {
    ulli ret = 0;
    while(x) {
        if( x & 1 ) ret = ( ret + y ) % mod;
        if( x >>= 1 ) y = ( y + y ) % mod;
    }
    return ret;
}
inline ulli fastpow(ulli base,ulli tim) {
    ulli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}

int main() {
    scanf("%llu%llu%llu",&n,&m,&l) , mod = n + 1;
    printf("%llu\n",mul(l,fastpow(n/2+1,m)));
    return 0;
}
