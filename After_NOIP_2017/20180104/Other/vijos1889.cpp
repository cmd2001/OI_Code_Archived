#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e6+1e2;

lli mu[maxn];

inline void gen() {
    static int prime[maxn],cnt;
    static char vis[maxn];
    for(int i=2;i<maxn;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i;
            mu[i] = 1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<maxn;j++) {
            vis[i*prime[j]] = 1;
            mu[i*prime[j]] = -mu[i];
            if( ! ( i % prime[j] ) ) {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
}

inline lli calc(lli x) {
    lli sq = sqrt(x),ret=0;
    for(lli i=1;i<=sq;i++) {
        ret += ( x / ( i * i ) ) * mu[i];
    }
    return ret;
}

inline lli getans(lli x) {
    lli l = 1 , r = 25505460948LL , mid;
    while( r != l + 1 ) {
        mid = ( l + r ) >> 1;
        if( calc(mid) >= x )
            r = mid;
        else
            l = mid;
    }
    return r;
}

int main() {
    gen();
    static lli k;
    
    scanf("%lld",&k);
    printf("%lld\n",getans(k));
    
    return 0;
}