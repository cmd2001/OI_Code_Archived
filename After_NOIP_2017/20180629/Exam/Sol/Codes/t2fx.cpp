#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=3e3+1e2;

namespace NTT {
    const int mod=998244353,g=3;
    inline int add(const int &x,const int &y) {
        const int ret = x + y;
        return ret >= mod ? ret - mod : ret;
    }
    inline int sub(const int &x,const int &y) {
        const int ret = x - y;
        return ret < 0 ? ret + mod : ret;
    }
    inline int mul(const int &x,const int &y) {
        return (lli) x * y % mod;
    }
    inline void mule(int &dst,const int &x) {
        dst = (lli) dst * x % mod;
    }
    inline int fastpow(int base,int tim) {
        int ret = 1;
        while(tim) {
            if( tim & 1 ) mule(ret,base);
            if( tim >>= 1 ) mule(base,base);
        }
        return ret;
    }
    inline void NTT(int* dst,int n,int tpe) {
        for(int i=0,j=0;i<n;i++) {
            if( i < j ) swap(dst[i],dst[j]);
            for(int t=n>>1;(j^=t)<t;t>>=1) ;
        }
        for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
            int per = fastpow(g,mod/len);
            if( !~tpe ) per = fastpow(per,mod-2);
            for(int st=0;st<n;st+=len) {
                int w = 1;
                for(int pos=0;pos<h;pos++) {
                    const int u = dst[st+pos] , v = mul(dst[st+pos+h],w);
                    dst[st+pos] = add(u,v) , dst[st+pos+h] = sub(u,v) , mule(w,per);
                }
            }
        }
        if( !~tpe ) {
            const int inv = fastpow(n,mod-2);
            for(int i=0;i<n;i++) mule(dst[i],inv);
        }
    }
    inline void mul(int* dst,int *sou,int ld,int ls) {
        int len; for(len=1;len<=ld+ls;len<<=1) ;
        for(int i=ld;i<len;i++) sou[i] = 0;
        for(int i=ls;i<len;i++) dst[i] = 0;
        NTT(dst,len,1) , NTT(sou,len,1);
        for(int i=0;i<len;i++) mule(dst[i],sou[i]);
        NTT(dst,len,-1);
    }
}

bool vis[maxn];
int fac[maxn],inv[maxn],f[2][maxn];
lli n,m,t;
int mod,p; // mod is mod of lucas and mod of answer .

inline int c(int n,int m) {
    if( n < m ) return 0;
    return fac[n] * inv[m] * inv[n-m] % mod;
}
inline void trans(int* dst,int* sou) {
    static int tp[maxn]; memset(tp,0,sizeof(tp));
    for(int i=0;i<p;i++) tp[i*mod%p] += sou[i];
    for(int i=0;i<p;i++) tp[i] %= mod;
    NTT::mul(dst,tp,p,p);
    for(int i=p;i<p<<1;i++) dst[i%p] += dst[i];
    for(int i=0;i<p;i++) dst[i] %= mod;
}
inline void initseq(int* dst,int bitn,int bitm,int bitt) {
    for(int i=0;i<p;i++) dst[i] = 0;
    for(int i=0;i<=bitn&&i<=bitt;i++) {
        dst[i%p] += c(bitn,i) * c(bitm,bitt-i) *  c(bitt,i) % mod;
    }
    for(int i=0;i<p;i++) dst[i] %= mod;
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline void init() {
    memset(f,0,sizeof(f));
    *fac = 1; for(int i=1;i<mod;i++) fac[i] = fac[i-1] * i % mod;
    inv[mod-1] = fastpow(fac[mod-1],mod-2); for(int i=mod-1;i;i--) inv[i-1] = inv[i] * i % mod;
}
inline void getbit(int* dst,int &len,lli x) {
    memset(dst,0,280) , len = 0;
    while(x) dst[++len] = x % mod , x /= mod;
}

template<typename T>
inline T read() {
    T  ret = 0; char ch;
    while( !isdigit(ch=getchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int bitn[70],bitm[70],bitt[70],tn,tm,tt;

int main() {
    static int T,siz,cur,ans;
    T = read<int>();
    while(T--) {
        n = read<lli>() , m = read<lli>() , t = read<lli>() , mod = read<int>() , memset(vis,0,p=read<int>()) , siz = read<int>();
        while(siz--) vis[read<int>()] = 1;
        init() , ans = 0 , getbit(bitn,tn,n) , getbit(bitm,tm,m) , getbit(bitt,tt,t);
        initseq(f[cur=0],bitn[tt],bitm[tt],bitt[tt]);
        for(int i=tt-1;i;i--) cur ^= 1 , initseq(f[cur],bitn[i],bitm[i],bitt[i]) , trans(f[cur],f[cur^1]);
        for(int i=0;i<p;i++) if( vis[i] ) ans += f[cur][i];
        printf("%d\n",ans%mod);
    }
    return 0;
}

