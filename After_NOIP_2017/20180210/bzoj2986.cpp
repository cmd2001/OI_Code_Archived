#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2,lim=2e5;

int mu[maxn];

inline void gen() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , mu[i] = -1;
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
            mu[i*prime[j]] = -mu[i];
        }
    }
}

inline lli calc(lli n) {
    lli ret = 0;
    for(lli i=2;i*i<=n;i++)
        ret -= mu[i] * n / ( i * i );
    return ret;
}
inline lli bin(lli x) {
    lli ll = 0 , rr = 30000000000ll , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( calc(mid) < x ) ll = mid;
        else rr = mid;
    }
    return rr;
}

int main() {
    static lli t;
    gen();
    scanf("%lld",&t);
    printf("%lld\n",bin(t));
    return 0;
}
