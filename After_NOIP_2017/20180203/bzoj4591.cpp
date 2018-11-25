#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=2510,p=2333;

int fac[maxn],ifac[maxn];
int mem[maxn][maxn];
bool vis[maxn][maxn];
inline int fastpow(int base,int tme,int mod) {
    int ret = 1;
    while( tme ) {
        if( tme & 1 ) ret = ret * base % mod;
        base = base * base % mod;
        tme >>= 1;
    }
    return ret;
}
inline void gen() {
    *fac = 1;
    for(int i=1;i<p;i++)
        fac[i] = fac[i-1] * i % p;
    ifac[p-1] = fastpow(fac[p-1],p-2,p);
    for(int i=p-2;~i;i--)
        ifac[i] = ifac[i+1] * ( i + 1 ) % p;
}
inline int c(lli n,lli m) {
    if( n < m ) return 0;
    if( n < p && m < p )
        return fac[n] * ifac[m] % p * ifac[n-m] % p;
    return c(n/p,m/p) * c(n%p,m%p) % p;
}
inline int brute(int n,int k) {
    vis[n][k] = 1;
    if( k == 0 ) return mem[n][k] = 1;
    return mem[n][k] = ( brute(n,k-1) + c(n,k) ) % p;
}
inline int s(lli n,lli k) {
    if( k < 0 ) return 0;
    if( k == 0 ) return 1;
    if( n < p && k < p ) {
        if( vis[n][k] ) return mem[n][k];
        else return brute(n,k);
    }
    return ( s(n/p,k/p-1) * s(n%p,p-1) % p + c(n/p,k/p) * s(n%p,k%p) % p ) % p;
}

int main() {
    static int t;
    static lli n,k;
    gen();
    scanf("%d",&t);
    while( t-- ) {
        scanf("%lld%lld",&n,&k);
        printf("%d\n",s(n,k));
    }
    return 0;
}
