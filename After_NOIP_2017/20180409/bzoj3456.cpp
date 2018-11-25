#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
const int maxn=262145;
const int mod=1004535809,g=21;

int fac[maxn],inv[maxn];
int F[maxn],G[maxn],C[maxn];
int n,len;

inline int fastpow(int base,lli tim) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = (lli) ret * base % mod;
        if( tim >>= 1 ) base = (lli) base * base % mod;
    }
    return ret;
}
inline void NTT(int* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        lli per = fastpow(g,mod/len);
        if( !~tpe ) per = fastpow(per,mod-2);
        for(int st=0;st<n;st+=len) {
            lli w = 1;
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = dst[st+pos+h] * w % mod;
                dst[st+pos] = ( (lli) u + v ) % mod ,
                dst[st+pos+h] = ( (lli) u - v + mod ) % mod ,
                w = (lli) w * per % mod;
            }
        }
    }
    if( !~tpe ) {
        const lli inv = fastpow(n,mod-2);
        for(int i=0;i<n;i++) dst[i] = dst[i] * inv % mod;
    }
}
inline void Inv(int* dst,const int* sou,int len) {
    static int tp[maxn];
    if( len == 1 ) return void(*dst=fastpow(*sou,mod-2));
    Inv(dst,sou,len>>1);
    memcpy(tp,sou,sizeof(int)*len) , memset(tp+len,0,sizeof(int)*len);
    NTT(dst,len<<1,1) , NTT(tp,len<<1,1);
    for(int i=0;i<len<<1;i++) dst[i] = dst[i] * ( 2 - (lli) dst[i] * tp[i] % mod + mod ) % mod;
    NTT(dst,len<<1,-1) , memset(dst+len,0,sizeof(int)*len);
}

inline void getans() {
    Inv(F,C,len);
    NTT(F,len,1) , NTT(G,len,1);
    for(int i=0;i<len;i++) F[i] = (lli) F[i] * G[i] % mod;
    NTT(F,len,-1);
}
inline int c(int n,int m) {
    return (lli) fac[n] * inv[m] % mod * inv[n-m] % mod;
}
inline void init() {
    C[0] = 1;
    for(int i=1;i<=n;i++) C[i] = (lli) fastpow(2,(lli)i*(i-1)>>1) * inv[i] % mod;
    for(int i=1;i<=n;i++) G[i] = (lli) fastpow(2,(lli)i*(i-1)>>1) * inv[i-1] % mod;
}
inline void pre() {
    *fac = 1;
    for(int i=1;i<=n;i++) fac[i] = (lli) fac[i-1] * i % mod;
    inv[n] = fastpow(fac[n],mod-2);
    for(int i=n;i;i--) inv[i-1] = (lli) inv[i] * i % mod;
}

int main() {
    scanf("%d",&n);
    for(len=1;len<=(n+1);len<<=1) ;
    pre() , init();
    getans() , printf("%lld\n",(lli)F[n]*fac[n-1]%mod);
    return 0;
}


