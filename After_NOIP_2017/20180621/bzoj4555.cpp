#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=262145;
const int mod=998244353,G=3;

inline int add(const int &a,const int &b) {
    const int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &a,const int &b) {
    const int ret = a - b;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
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
inline int supows(int x,int n) {
    if( x == 1 ) return n + 1;
    return mul(sub(fastpow(x,n+1),1),fastpow(sub(x,1),mod-2));
}

int f[maxn],g[maxn],ans[maxn],pows2[maxn],pows1[maxn],fac[maxn],inv[maxn];
int n,len,su;

int main() {
    scanf("%d",&n);
    for(len=1;len<=n;len<<=1);
    *fac = 1; for(int i=1;i<=n;i++) fac[i] = mul(fac[i-1],i);
    inv[n] = fastpow(fac[n],mod-2); for(int i=n;i;i--) inv[i-1] = mul(inv[i],i);
    *pows2 = 1; for(int i=1;i<=n;i++) pows2[i] = add(pows2[i-1],pows2[i-1]);
    *pows1 = 1; for(int i=1;i<=n;i++) pows1[i] = mul(pows1[i-1],mod-1);
    for(int i=0;i<=n;i++) f[i] = mul(supows(i,n),inv[i]);
    for(int i=0;i<=n;i++) g[i] = mul(pows1[i],inv[i]);
    NTT(f,len<<1,1) , NTT(g,len<<1,1);
    for(int i=0;i<len<<1;i++) ans[i] = mul(f[i],g[i]);
    NTT(ans,len<<1,-1);
    for(int i=0;i<=n;i++) adde(su,mul(ans[i],mul(pows2[i],fac[i])));
    printf("%d\n",su);
    return 0;
}

