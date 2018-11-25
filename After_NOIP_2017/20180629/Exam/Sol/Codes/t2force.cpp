#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef long long int lli;
using namespace std;
const int maxe=1e3+1e2;

lli fac[maxe],inv[maxe];
bool vis[maxe];
int mod,p;

inline lli lucas(lli n,lli m) {
    if( n < m ) return 0;
    if( n < mod && m < mod ) return fac[n] * inv[m] * inv[n-m] % mod;
    return lucas(n/mod,m/mod) * lucas(n%mod,m%mod) % mod;
}
inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

template<typename T>
inline T read() {
    T ret = 0; char ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int T,siz;
    static lli n,m,t,ans;
    T = read<int>();
    while(T--) {
        n = read<lli>() , m = read<lli>() , t = read<lli>() , mod = read<int>() , memset(vis,0,p=read<int>()) , siz = read<int>() , ans = 0;
        while( siz-- ) vis[read<int>()] = 1;
        *fac = 1; for(int i=1;i<mod;i++) fac[i] = fac[i-1] * i % mod;
        inv[mod-1] = fastpow(fac[mod-1],mod-2); for(int i=mod-1;~i;i--) inv[i-1] = inv[i] * i % mod;
        for(lli i=0;i<=n;i++) if( vis[i%p] ) ans += lucas(n,i) * lucas(m,t-i) * lucas(t,i) % mod , ans %= mod;
        printf("%lld\n",ans);
    }
    return 0;
}
