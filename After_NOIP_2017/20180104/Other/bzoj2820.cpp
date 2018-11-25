#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e7+1e2;

lli f[maxn];

inline void getf() {
    static int mu[maxn],prime[maxn],cnt;
    static char vis[maxn];
    
    mu[1] = 1;
    for(int i=2;i<maxn;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i,
            mu[i] = -1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<maxn;j++) {
            vis[i*prime[j]] = 1;
            mu[i*prime[j]] = -mu[i];
            if( !( i % prime[j] ) ) {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    for(int i=1;i<=cnt;i++) {
        const int p = prime[i];
        for(int j=1;j*p<maxn;j++)
            f[j*p] += mu[j];
    }
    for(int i=1;i<maxn;i++)
        f[i] += f[i-1];
}

inline lli calc(lli n,lli m) {
    const lli mi = min(n,m);
    lli ret = 0;
    for(lli i=1,j;i<=mi;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += ( f[j] - f[i-1] ) * ( n / i ) * ( m / i );
    }
    return ret;
}

int main() {
    static int t;
    static lli n,m;
    getf();
    
    scanf("%d",&t);
    while( t-- ) {
        scanf("%lld%lld",&n,&m);
        printf("%lld\n",calc(n,m));
    }
    
    return 0;
}