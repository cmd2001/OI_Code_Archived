#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e7+1e2,mx=1e7;
const int mod=1e8+9;

lli sum[maxn];

inline void pre() {
    static int prime[maxn],cnt;
    static char vis[maxn];
    sum[1] = 1;
    for(lli i=2;i<=mx;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i;
            sum[i] = 1 - i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=mx;j++) {
            vis[i*prime[j]] = 1;
            sum[i*prime[j]] = sum[i] * sum[prime[j]] % mod;
            if( ! ( i % prime[j]) ) {
                sum[i*prime[j]] = ( sum[i] ) % mod;
                break;
            }
        }
    }
    for(int i=1;i<=mx;i++) {
        sum[i] = sum[i] * i % mod,
        sum[i] += sum[i-1],
        sum[i] = ( sum[i] % mod + mod ) % mod;
    }
}

inline lli calc(lli n,lli m,lli step) {
    n /= step , m /= step;
    return ( ( ( n + 1 ) * n >> 1 ) % mod ) * ( ( ( m + 1 ) * m >> 1 ) % mod ) % mod;
}
inline lli query(lli n,lli m) {
    lli ret = 0 , lim = min( n , m );
    for(lli i=1,j;i<=lim;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += calc(n,m,i) * ( ( sum[j] - sum[i-1] ) % mod + mod ) % mod;
        ret = ( ret % mod + mod ) % mod;
    }
    return ret;
}

int main() {
    static int t,n,m;
    pre();
    scanf("%d",&t);
    while( t-- ) {
        scanf("%d%d",&n,&m);
        printf("%lld\n",query(n,m));
    }
    return 0;
}