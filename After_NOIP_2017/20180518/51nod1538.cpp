#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef unsigned int uint;
typedef unsigned long long int ulli;
const int maxn=131075<<1;
const uint mod=104857601,g=3;
const uint lim=23333;

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
uint pw[18][maxn],paw[18][maxn];

__inline uint fastpow(uint base,uint tim) {
    uint ret = 1;
    while(tim) {
        if( tim &  1 ) ret = mul(ret,base);
        tim >>= 1 , base = mul(base,base);
    }
    return ret;
}

__inline void NTT_pre(uint n) {
    for(uint len=2,h=1,lo=1;len<=n;len<<=1,h<<=1,++lo) {
        uint per = fastpow(g,mod/len) , aper = fastpow(per,mod-2);
        uint w = 1 , aw = 1;
        for(uint pos=0;pos<h;pos++) pw[lo][pos] = w  , paw[lo][pos] = aw , w = mul(w,per) , aw = mul(aw,aper);
    }
}

__inline void NTT(uint* dst,uint n,int ope) {
    for(uint i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(uint t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(uint len=2,h=1,lo=1;len<=n;len<<=1,h<<=1,++lo) {
        uint *w = ope == -1 ? paw[lo] : pw[lo];
        for(uint st=0;st<n;st+=len) {
            for(uint pos=0;pos<h;pos++) {
                const uint u = dst[st+pos] , v = mul(dst[st+pos+h],w[pos]);
                dst[st+pos] = add(u,v) , dst[st+pos+h] = sub(u,v);
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

__inline void division(uint* a,uint* b,uint* d,uint* r,uint n,uint m) { // n is length of a , m is length of b .
    static uint ra[maxn],rb[maxn],invb[maxn];
    
    while(n&&!a[n-1]) --n;
    while(m&&!b[m-1]) --m;
    if( n < m ) return void(memcpy(r,a,m<<2));
    uint len;
    for(len=1;len<(n-m+1)<<1;len<<=1) ;
    if( n < len ) memset(a+n,0,(len-n)<<2);
    if( m < len ) memset(b+m,0,(len-m)<<2);
    
    memcpy(ra,a,n<<2) , memcpy(rb,b,m<<2); // we must copy full array in order to reverse it correctly .
    if( m < len ) memset(rb+m,0,(len-m)<<2);
    std::reverse(ra,ra+n) , std::reverse(rb,rb+m);
    memset(invb,0,len<<2) , inverse(invb,rb,len);
    
    memset(ra+n-m+1,0,(len-n+m-1)<<2) , memset(invb+n-m+1,0,(len-n+m-1)<<2); // we must fix ra's and invb's length to n - m length .
    NTT(ra,len,1) , NTT(invb,len,1);
    for(uint i=0;i<len;i++) d[i] = mul(ra[i],invb[i]);
    NTT(d,len,-1) , std::reverse(d,d+n-m+1) , memset(d+n-m+1,0,(len-n+m-1)<<2);
    
    
    for(len=1;len<n;len<<=1) ;
    if( n < len ) memset(a+n,0,(len-n)<<2);
    if( m < len ) memset(b+m,0,(len-m)<<2);
    if( n - m +1 < len ) memset(d+n-m+1,0,(len-n+m-1)<<2);
    
    memcpy(ra,a,len<<2) , memcpy(rb,b,len<<2) , memcpy(invb,d,len<<2); // now ra is a , rb is b , invb is d .
    NTT(ra,len,1) , NTT(rb,len,1) , NTT(invb,len,1);
    for(uint i=0;i<len;i++) r[i] = sub(ra[i],mul(rb[i],invb[i]));
    NTT(r,len,-1) , memset(r+n,0,(len-n)<<2);
}

__inline void sqr(uint* dst,uint* mod,uint n,uint m) { // n is length of dst , m is length of mod .
    static uint d[maxn],r[maxn];
    uint len;
    for(len=1;len<n<<1;len<<=1) ;
    if( n < len ) memset(dst+n,0,(len-n)<<2);
    
    NTT(dst,len,1);
    for(uint i=0;i<len;i++) dst[i] = mul(dst[i],dst[i]);
    NTT(dst,len,-1);
    
    division(dst,mod,d,r,(n<<1),m) , memcpy(dst,r,m<<2);
}


__inline void calc(uint* ans,uint* trs,ulli tim) { // high-bit fastpower .
    int len = 0; *ans = 1; // init ans with 1 .
    while( (1ull << len ) <= tim ) ++len;
    while( ~len ) {
        sqr(ans,trs,lim+2,lim+2);
        if( ( tim >> len ) & 1u ) { // simulate a multi with 1 moding mod .
            for(uint i=lim;i;i--) ans[i] = ans[i-1];
            *ans = 0;
            for(uint i=0;i<lim;i++) ans[i] = sub(ans[i],mul(ans[lim],trs[i]));
            ans[lim] = 0;
        }
        --len;
    }
}

int main() {
    static uint n,a,A,B;
    static ulli m;
    scanf("%u%llu%u%u%u",&n,&m,&a,&A,&B);
    for(uint i=1;i<=n;i++) {
        if( a <= 23333 ) ++trs[lim-a];
        a = ( (ulli) a * A + B ) % 23333 + 1;
    }
    for(uint i=0;i<=lim;i++) if(trs[i]) trs[i] = mod - trs[i];
    trs[lim] = 1;
    NTT_pre(131072u) , calc(ans,trs,m+lim-1) , printf("%d\n",ans[lim-1]);  
    return 0;
}
