#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=262145;
const int mod=998244353,inv=(mod+1)>>1;

int a[maxn],aa[maxn],aaa[maxn],b[maxn],bb[maxn],bbb[maxn];

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
    if((dst += x) >= mod) dst -= mod;
}
inline void sube(int &dst,const int &x) {
    if((dst -= x) < 0) dst += mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}

inline void fwt_or(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) for(int st=0;st<n;st+=len) for(int pos=0;pos<h;pos++) adde(dst[st+pos+h],dst[st+pos]);
}
inline void fwt_and(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) for(int st=0;st<n;st+=len) for(int pos=0;pos<h;pos++) adde(dst[st+pos],dst[st+pos+h]);
}
inline void fwt_xor(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) for(int st=0;st<n;st+=len) for(int pos=0;pos<h;pos++) {
        const int u = dst[st+pos], v = dst[st+pos+h];
        dst[st+pos] = add(u,v), dst[st+pos+h] = sub(u,v);
    }
}
inline void ufwt_or(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) for(int st=0;st<n;st+=len) for(int pos=0;pos<h;pos++) sube(dst[st+pos+h],dst[st+pos]);
}
inline void ufwt_and(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) for(int st=0;st<n;st+=len) for(int pos=0;pos<h;pos++) sube(dst[st+pos],dst[st+pos+h]);
}
inline void ufwt_xor(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) for(int st=0;st<n;st+=len) for(int pos=0;pos<h;pos++) {
        const int u = dst[st+pos], v = dst[st+pos+h];
        dst[st+pos] = mul(add(u,v),inv), dst[st+pos+h] = mul(sub(u,v),inv);
    }
}

int main() {
    static int n,len;
    scanf("%d",&n), len = (n = 1 << n);
    for(int i=0,t;i<n;i++) scanf("%d",&t), a[i] = aa[i] = aaa[i] = t;
    for(int i=0,t;i<n;i++) scanf("%d",&t), b[i] = bb[i] = bbb[i] = t;
    fwt_or(a,len), fwt_or(b,len), fwt_and(aa,len), fwt_and(bb,len), fwt_xor(aaa,len), fwt_xor(bbb,len);
    for(int i=0;i<len;i++) mule(a[i],b[i]), mule(aa[i],bb[i]), mule(aaa[i],bbb[i]);
    ufwt_or(a,len), ufwt_and(aa,len), ufwt_xor(aaa,len);
    for(int i=0;i<len;i++) printf("%d%c",a[i],"\n "[i!=len-1]);
    for(int i=0;i<len;i++) printf("%d%c",aa[i],"\n "[i!=len-1]);
    for(int i=0;i<len;i++) printf("%d%c",aaa[i],"\n "[i!=len-1]);
    return 0;
}
