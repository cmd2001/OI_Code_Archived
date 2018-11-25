#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxt=20;

lli fac[maxn],inv[maxn],ans;
lli in[maxt];
int n,m,t,mod;

inline lli c(lli n,lli m) {
    if( n < m ) return 0;
    if( n < mod && m < mod ) return fac[n] * inv[m] % mod * inv[n-m] % mod;
    return c(n%mod,m%mod) * c(n/mod,m/mod) % mod;
}
inline lli calc(lli n,lli m) {
    if( !m ) return n == 0;
    if( n < 0 ) return 0;
    return c(n+m,m);
}
inline lli calcase(int sel,lli su) {
    return sel & 1 ? mod - calc(m-su,n) : calc(m-su,n);
}
inline void dfs(int pos,int sel,lli su) {
    if( pos > t ) return void(ans=(ans+calcase(sel,su))%mod);
    dfs(pos+1,sel,su) , dfs(pos+1,sel+1,su+in[pos]+1);
}

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline void pre() {
    *fac = 1;
    for(int i=1;i<mod;i++) fac[i] = fac[i-1] * i % mod;
    inv[mod-1] = fastpow(fac[mod-1],mod-2);
    for(int i=mod-1;i;i--) inv[i-1] = inv[i] * i % mod;
}

int main() {
    scanf("%d%d%d%d",&n,&t,&m,&mod) , pre();
    for(int i=1;i<=t;i++) scanf("%lld",in+i);
    dfs(1,0,0);
    printf("%lld\n",ans);
    return 0;
}
