#pragma GCC optimize(3) 
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
const int maxn=262145;
const int mod=998244353,g=3,inv2=499122177;

int len=1;

inline int fastpow(int base,int tim,const int mod) {
    int ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = (lli) ret * base % mod;
        base = (lli) base * base % mod;
        tim >>= 1;
    }
    return ret;
}
inline void NTT(int* dst,const int n,const int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap( dst[i] ,dst[j] );
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        int per = fastpow( g , mod / len , mod );
        if( !~ope ) per = fastpow( per , mod - 2 , mod );
        for(int st=0;st<n;st+=len) {
            int w = 1;
            for(int pos=0;pos<(len>>1);pos++) {
                const int u = dst[st+pos] , v = (lli) dst[st+pos+(len>>1)] * w % mod;
                dst[st+pos] = ( u + v ) % mod ,
                dst[st+pos+(len>>1)] = ( u - v + mod ) % mod ,
                w = (lli) w * per % mod;
            }
        }
    }
    if( !~ope ) {
        const int inv = fastpow( n , mod - 2 , mod );
        for(int i=0;i<n;i++) dst[i] = (lli) dst[i] * inv % mod;
    }
}

int tp[maxn],invb[maxn];

inline void Inv(int* dst,const int* sou,const int len) {
    if( len == 1 ) {
        *dst = fastpow( *sou , mod - 2 , mod );
        return;
    }
    Inv(dst,sou,len>>1);
    memcpy(tp,sou,sizeof(int)*len) , memset(tp+len,0,sizeof(int)*len);
    NTT(dst,len<<1,1) , NTT(tp,len<<1,1);
    for(int i=0;i<len<<1;i++) // every point value will be 2 after doing NTT on 2 .
        dst[i] = dst[i] * ( 2 - (lli) dst[i] * tp[i] % mod + mod ) % mod;
    NTT(dst,len<<1,-1) , memset(dst+len,0,sizeof(int)*len);
}
inline void Sqrt(int* dst,const int* sou,const int len) {
    if( len == 1 ) { // 1 is a SPECIAL VALUE in THIS PROBLEM .
        *dst = 1;
        return;
    }
    Sqrt(dst,sou,len>>1);
    memset(invb,0,sizeof(int)*len) , Inv(invb,dst,len);
    memcpy(tp,sou,sizeof(int)*len) , memset(tp+len,0,sizeof(int)*len);
    NTT(dst,len<<1,1) , NTT(tp,len<<1,1) , NTT(invb,len<<1,1);
    for(int i=0;i<len<<1;i++) dst[i] = ( dst[i] + (lli) tp[i] * invb[i] % mod ) * inv2 % mod;
    NTT(dst,len<<1,-1) , memset(dst+len,0,sizeof(int)*len);
}

int c[maxn],sqrtc[maxn],invc[maxn];

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    while( len <= m  ) len <<= 1;
    for(int i=1,p;i<=n;i++) {
        scanf("%d",&p);
        if( p <= m ) c[p] = 1;
    }
    for(int i=1;i<len;i++) c[i] = ( - c[i] * 4 + mod ) % mod;
    *c = 1;
    Sqrt(sqrtc,c,len);
    ++*sqrtc;
    Inv(invc,sqrtc,len);
    for(int i=1;i<=m;i++)
        printf("%d\n",(invc[i]<<1)%mod);
    return 0;
}

