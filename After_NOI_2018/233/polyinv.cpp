#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn = 262145;
const int mod = 998244353, G = 3, IG = (mod + 1) / 3;

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
inline void mule(int& dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if(tim & 1) mule(ret,base);
        if(tim >>= 1) mule(base,base);
    }
    return ret;
}

inline void NTT(int* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if(i < j) swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1);
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        const int per = fastpow(ope == 1 ? G : IG, mod / len);
        for(int st=0;st<n;st+=len) {
            int w = 1;
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos], v = mul(dst[st+pos+h],w);
                dst[st+pos] = add(u,v), dst[st+pos+h] = sub(u,v), mule(w,per);
            }
        }
    }
    if(!~ope) {
        const int inv = fastpow(n,mod-2);
        for(int i=0;i<n;i++) mule(dst[i],inv);
    }
}

int in[maxn],inv[maxn],A[maxn];

inline void poly_inv(int* dst,const int* sou,int n) {
    if(n == 1) return void(*dst = fastpow(*sou,mod-2));
    poly_inv(dst,sou,n>>1), memcpy(A,sou,sizeof(int)*n), memset(A+n,0,sizeof(int)*n);
    NTT(A,n<<1,1), NTT(dst,n<<1,1);
    //for(int i=0;i<n<<1;i++) dst[i] = sub(mul(2,dst[i]),mul(mul(dst[i],dst[i]),a[i]));
    for(int i=0;i<n<<1;i++) dst[i] = mul(dst[i],sub(2,mul(dst[i],A[i]))); // a better expression.
    NTT(dst,n<<1,-1), memset(dst+n,0,sizeof(int)*n);
}

int main() {
    static int n,len;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",in+i);
    for(len=1;len<=n;len<<=1);
    poly_inv(inv,in,len);
    for(int i=0;i<n;i++) printf("%d%c",inv[i],"\n "[i!=n-1]);
    return 0;
}

