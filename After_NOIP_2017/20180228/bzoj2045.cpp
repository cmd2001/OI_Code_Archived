#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2,lim=1e6;

lli su[maxn];

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    su[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , su[i] = -1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( i % prime[j] ) su[tar] = -su[i];
            else break;
        }
    }
    for(int i=1;i<=lim;i++) su[i] += su[i-1];
}
inline lli calc(lli n,lli m) {
    lli ret = 0;
    if( n > m ) swap(n,m); // now assert n <= m .
    for(lli i=1,j;i<=n;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += ( su[j] - su[i-1] ) * ( n / i ) * ( m / i );
    }
    return ret;
}

int main() {
    static lli a,b,d;
    scanf("%lld%lld%lld",&a,&b,&d) , sieve();
    printf("%lld\n",calc(a/d,b/d));
    return 0;
}

