#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=4e5+1e2;

lli in[maxn],ans;
lli c[maxn],modc[maxn];
lli fac[maxn],tim[maxn];
lli dvs[maxn],tms[maxn],pows[maxn];
int n,mod,now,psnow,cnt;

inline lli fastpow(lli base,lli tim,lli mod) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline lli exgcd(lli a,lli b,lli& x,lli& y) {
    if( !b ) return x = 1 , y = 0 , a;
    lli ret = exgcd(b,a%b,y,x);
    y -= a / b * x;
    return ret;
}
inline lli inv(lli t,lli mod) {
    static lli x,y;
    exgcd(t,mod,x,y);
    return ( x % mod + mod ) % mod;
}
inline void getcoprime(int x,int& retc,int& rett) {
    retc = x , rett = 0;
    while( ! ( retc % now ) ) retc /= now , ++rett;
}
inline void preseq() {
    fac[0] = 1 , tim[0] = 0;
    for(int i=1,c,t;i<=n;i++) {
        getcoprime(i,c,t);
        fac[i] = fac[i-1] * c % psnow , tim[i] = tim[i-1] + t;
    }
}
inline void getdvs(int x) {
    for(int i=2;(lli)i*i<=x;i++)
        if( ! ( x % i ) ) {
            dvs[++cnt] = i , pows[cnt] = 1;
            while( ! ( x % i ) ) ++tms[cnt] , pows[cnt] *= i , x /= i;
        }
    if( x != 1 ) dvs[++cnt] = x , pows[cnt] = x , tms[cnt] = 1;
}
inline void cnow(int x,int& retc,int& rett) {
    retc = fac[n-1] * inv(fac[x],psnow) % psnow * inv(fac[n-1-x],psnow) % psnow;
    rett = tim[n-1] - tim[x] - tim[n-1-x];
}
inline void merge(int x,int fac,int tim) {
    lli cur = (lli) fac * fastpow(now,tim,mod) % mod;
    c[x] = ( c[x] + cur * ( mod / psnow ) % mod * inv( mod / psnow , psnow ) % mod ) % mod;
}


int main() {
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);
    scanf("%d%d",&n,&mod);
    for(int i=1;i<=n;i++) scanf("%lld",in+i);
    getdvs(mod);
    for(int i=1;i<=cnt;i++) {
        now = dvs[i] , psnow = pows[i] , preseq();
        for(int j=0,c,t;j<n;j++) cnow(j,c,t) , merge(j,c,t);
    }
    for(int i=1;i<=n;i++) ( ans += in[i] * c[i-1] % mod ) %= mod;
    printf("%lld\n",ans);
    fclose(stdout);
    return 0;
}

