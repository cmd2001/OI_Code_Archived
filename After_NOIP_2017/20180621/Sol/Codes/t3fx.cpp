#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=131073;
const int mod=1004535809,G=3;

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
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
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
        int per = fastpow(G,mod/len);
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
inline void INV(int* dst,const int* sou,int len) {
    static int tp[maxn];
    if( len == 1 ) return void( *dst = fastpow(*sou,mod-2) );
    INV(dst,sou,len>>1) , memcpy(tp,sou,len<<2) , memset(tp+len,0,len<<2);
    NTT(dst,len<<1,1) , NTT(tp,len<<1,1);
    for(int i=0;i<len<<1;i++) dst[i] = mul(dst[i],sub(2,mul(dst[i],tp[i])));
    NTT(dst,len<<1,-1) , memset(dst+len,0,len<<2);
}

int fac[maxn],inv[maxn],strl[21][21];
inline int c(int n,int m) {
    return mul(fac[n],mul(inv[m],inv[n-m]));
}

int f[16][maxn],g[maxn],ways[maxn];
const int len = 65536;

namespace GetG {
    int b[maxn],c[maxn],invb[maxn];
    inline void work() {
        for(int i=0;i<len;i++) b[i] = mul(ways[i],inv[i]);
        for(int i=1;i<len;i++) c[i] = mul(ways[i],inv[i-1]);
        INV(invb,b,len) , NTT(invb,len<<1,1) , NTT(c,len<<1,1);
        for(int i=0;i<len<<1;i++) g[i] = mul(invb[i],c[i]);
        NTT(g,len<<1,-1) , g[0] = 0 , memset(g+len,0,len<<2);
        for(int i=1;i<len;i++) mule(g[i],fac[i-1]);
    }
}

namespace GetF {
    inline void work() {
        for(int i=1;i<len;i++) mule(g[i],inv[i]);
        for(int i=0;i<len;i++) f[0][i] = mul(ways[i],inv[i]);
        NTT(g,len<<1,1) , NTT(f[0],len<<1,1);
        for(int j=1;j<16;j++) {
            for(int i=0;i<len<<1;i++) f[j][i] = mul(f[j-1][i],g[i]);
            NTT(f[j],len<<1,-1) , memset(f[j]+len,0,len<<2) , NTT(f[j],len<<1,1);
        }
        for(int j=0;j<16;j++) {
            NTT(f[j],len<<1,-1);
            for(int i=0;i<len;i++) mule(f[j][i],fac[i]);
        }
    }
}

inline int getans(int n,int k) {
    int ret = 0;
    for(int i=0;i<=k;i++) adde(ret,mul(f[i][n],strl[k][i]));
    return ret;
}

inline void pre() {
    *fac = 1; for(int i=1;i<len;i++) fac[i] = mul(fac[i-1],i);
    inv[len-1] = fastpow(fac[len-1],mod-2); for(int i=len-1;i;i--) inv[i-1] = mul(inv[i],i);
    for(int i=0;i<len;i++) ways[i] = fastpow(2,((lli)i*(i-1)>>1)%(mod-1));
    strl[0][0] = 1;
    for(int i=1;i<16;i++) {
        strl[i][0] = 0;
        for(int j=1;j<=i;j++) strl[i][j] = add(strl[i-1][j-1],mul(j,strl[i-1][j]));
    }
}

int main() {
    static int t,n,k;
    pre() , GetG::work() , GetF::work();
    scanf("%d",&t);
    while(t--) scanf("%d%d",&n,&k) , printf("%d\n",mul(getans(n,k),fastpow(ways[n],mod-2)));
    return 0;
}
