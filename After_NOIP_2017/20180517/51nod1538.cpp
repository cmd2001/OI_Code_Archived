#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
typedef unsigned int uint;
typedef unsigned long long int ulli;
const int maxn=131075;
const uint mod=104857601,g=3;
//const uint lim=23333;
const uint lim = 15;

__inline uint add(const uint &a,const uint &b) {
    uint r = a + b;
    return r >= mod ? r - mod : r;
}
__inline uint sub(const uint &a,const uint &b) {
    uint r = a + mod - b;
    return r >= mod ? r - mod : r;
}
__inline uint mul(const uint &a,const uint &b) {
    return (ulli) a * b % mod;
}

uint ans[maxn],trs[maxn],bas[maxn];

__inline uint fastpow(uint base,uint tim) {
    uint ret = 1;
    while(tim) {
        if( tim &  1 ) ret = mul(ret,base);
        tim >>= 1 , base = mul(base,base);
    }
    return ret;
}

__inline void NTT(uint* dst,uint n,int ope) {
    for(uint i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(uint t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(uint len=2,h=1;len<=n;len<<=1,h<<=1) {
        uint per = fastpow(g,mod/len);
        if( !~ope ) per = fastpow(per,mod-2);
        for(uint st=0;st<n;st+=len) {
            uint w = 1;
            for(uint pos=0;pos<h;pos++) {
                const uint u = dst[st+pos] , v = mul(dst[st+pos+h],w);
                dst[st+pos] = add(u,v) , dst[st+pos+h] = sub(u,v) , w = mul(w,per);
            }
        }
    }
    if( !~ope ) {
        const uint inv = fastpow(n,mod-2);
        for(uint i=0;i<n;i++) dst[i] = mul(dst[i],inv);
    }
}

inline void inverse(uint* dst,const uint* sou,uint n) { // assert sizeof int == 4 .
    static uint tp[maxn];
    if( n == 1 ) return void( *dst = fastpow(*sou,mod-2) ) ;
    const uint len = n >> 1 ; inverse(dst,sou,len);
    memcpy(tp,sou,n<<2) , memset(tp+n,0,n<<2);
    NTT(dst,n<<1,1) , NTT(tp,n<<1,1);
    for(uint i=0;i<n<<1;i++) dst[i] = mul(dst[i],sub(2,mul(tp[i],dst[i])));
    NTT(dst,n<<1,-1) , memset(dst+n,0,n<<2);
}

inline void division(uint* a,uint* b,uint* d,uint* r,uint n,uint m) { // n is length of a , m is length of b .
    static uint ra[maxn],rb[maxn],invb[maxn];
    
    uint len;
    for(len=1;len<(n-m+1)<<1;len++) ;
    if( n < len ) memset(a+n,0,(len-n)<<2);
    if( m < len ) memset(b+m,0,(len-m)<<2);
    
    memcpy(ra,a,n<<2) , memcpy(rb,b,m<<2); // we must copy full array in order to reverse it correctly .
    std::reverse(ra,ra+n) , std::reverse(rb,rb+m);
    memset(invb,0,len<<2) , inverse(invb,rb,len);
    
    NTT(ra,len,1) , NTT(invb,len,1);
    for(uint i=0;i<len;i++) d[i] = mul(ra[i],invb[i]);
    NTT(d,len,-1) , std::reverse(d,d+len);
    
    for(len=1;len<n;len<<=1) ;
    if( n < len ) memset(a+n,0,(len-n)<<2);
    if( m < len ) memset(b+m,0,(len-m)<<2);
    if( n - m < len ) memset(d+n-m,0,(len-n+m)<<2);
    
    memcpy(ra,a,len<<2) , memcpy(rb,b,len<<2) , memcpy(invb,d,len<<2); // now ra is a , rb is b , invb is d .
    NTT(ra,len,1) , NTT(rb,len,1) , NTT(invb,len,1);
    for(uint i=0;i<len;i++) r[i] = sub(ra[i],mul(rb[i],invb[i]));
    NTT(r,len,-1);
}

inline void sqr(uint* dst,uint* mod,uint n,uint m) { // n is length of dst , m is length of mod .
    static uint d[maxn],r[maxn];
    uint len;
    for(len=1;len<n<<1;len<<=1) ;
    if( n < len ) memset(dst+n,0,(len-n)<<2);
    
    NTT(dst,len,1);
    for(uint i=0;i<len;i++) dst[i] = mul(dst[i],dst[i]);
    NTT(dst,len,-1);
    
    division(dst,mod,d,r,(n<<1)-1,m) , memcpy(dst,r,m<<2);
}

inline void fastpow(ulli tim) {
    *ans = 1;
    while(tim) {
        if( tim & 1 ) {
            for(uint i=lim;i;i--) ans[i] = ans[i-1];
            ans[0] = 0;
            for(uint i=0;i<lim;i++) ans[i] = sub(ans[i],mul(ans[lim],bas[i]));
            for(int i=1;i<lim;i++) debug<<ans[i]<<" "; debug<<endl;
            ans[lim] = 0;
        }
        if( tim >>= 1 ) sqr(bas,trs,lim,lim);
    }
}

int main() {
    static uint n,a,A,B;
    static ulli m;
    scanf("%u%llu%u%u%u",&n,&m,&a,&A,&B);
    for(uint i=1;i<=n;i++) {
        debug<<"a = "<<a<<endl;
        ++trs[a] , a = ( (ulli) a * A + B ) % lim + 1;
    }
    for(uint i=0;i<lim;i++) if( trs[i] ) trs[i] = mod - trs[i];
    fastpow(m) , printf("%u\n",ans[lim-1]);
    return 0;
}

/*
5 6 1 1 1

8
*/