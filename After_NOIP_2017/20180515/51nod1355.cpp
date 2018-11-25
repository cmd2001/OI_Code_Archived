#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e6+1e2,lim=1e6;
const int mod=1e9+7;

lli f[maxn],g[maxn];
bool vis[maxn];

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    g[1] = f[1] = 1;
    for(int i=2;i<=lim;i++) {
        g[i] = f[i] = ( f[i-1] + f[i-2] ) % mod;
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
    for(int i=1;i<=lim;i++) {
        lli inv = fastpow(g[i],mod-2);
        for(int j=i+i;j<=lim;j+=i) g[j] = g[j] * inv % mod;
    }
}
inline lli calc() {
    lli ret = 1;
    for(int i=1;i<=lim;i++) {
        bool used = 0;
        for(int j=i;j<=lim;j+=i) used |= vis[j];
        if( used ) ret = ret * g[i] % mod;
    }
    return ret;
}

int main() {
    static int n,t;
    scanf("%d",&n) , sieve();
    while(n--) scanf("%d",&t) , vis[t] = 1;
    printf("%lld\n",calc());
    return 0;
}
