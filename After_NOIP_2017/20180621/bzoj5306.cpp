#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=262145,maxe=1e7+1e2;
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
    if( ( dst += x ) >= mod )  dst -= mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1) mule(base,base);
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

int fac[maxe],inv[maxe];
int w[maxn],f[maxn],g[maxn];
int n,m,s,e,len,ans;

inline void pre() {
    const int lim = max(n,m);
    *fac = 1; for(int i=1;i<=lim;i++) fac[i] = mul(fac[i-1],i);
    inv[lim] = fastpow(fac[lim],mod-2); for(int i=lim;i;i--) inv[i-1] = mul(inv[i],i);
    for(len=1;len<=e;len<<=1) ;
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint() , s = getint() , e = min( n / s , m ) , pre();
    for(int i=0;i<=m;i++) w[i] = getint();
    for(int i=0;i<=e;i++) f[i] = mul(w[i],inv[i]);
    for(int i=0,t=1;i<=e;i++) g[i] = mul(t,inv[i]) , t = mod - t;
    NTT(f,len<<1,1) , NTT(g,len<<1,1);
    for(int i=0;i<len<<1;i++) w[i] = mul(f[i],g[i]);
    NTT(w,len<<1,-1);
    for(int i=0,pows=1;i<=e;i++) adde(ans,mul(fastpow(m-i,n-i*s),mul(mul(fac[n],fac[m]),mul(mul(w[i],inv[m-i]),mul(inv[n-i*s],pows))))) , mule(pows,inv[s]);
    printf("%d\n",ans);
    return 0;
}

