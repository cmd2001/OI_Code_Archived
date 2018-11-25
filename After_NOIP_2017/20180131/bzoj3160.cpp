#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=262145;
const double pi = acos(-1.0);
const int mod = 1e9 + 7;

struct Comp {
    double r,i;
    Comp() {}
    Comp(int rr) { r = rr , i = 0; }
    Comp(double rr) { r = rr , i = 0; }
    Comp(double rr,double ii) { r = rr , i = ii ; }
    friend Comp operator + (const Comp &a,const Comp &b) { return Comp(a.r+b.r,a.i+b.i); }
    friend Comp operator - (const Comp &a,const Comp &b) { return Comp(a.r-b.r,a.i-b.i); }
    friend Comp operator * (const Comp &a,const Comp &b) { return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r); };
}sou[maxn],dst[maxn];

char in[maxn];
lli pows[maxn];
int n,len=1;
lli ans;

inline void FFT(Comp* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap( dst[i] , dst[j] );
        for(int t = n >> 1 ; ( j ^= t ) < t ; t >>= 1 ) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const Comp per = Comp( cos( pi * ope / ( len >> 1 ) ) , sin( pi * ope / ( len >> 1 ) ) );
        for(int st=0;st<n;st+=len) {
            Comp w = Comp( 1 , 0 );
            for(int pos=0;pos<len>>1;++pos) {
                Comp u = dst[st+pos] , v = dst[st+pos+(len>>1)] * w;
                dst[st+pos] = u + v ,
                dst[st+pos+(len>>1)] = u - v ,
                w = w * per;
            }
        }
    }
    if( !~ope ) {
        for(int i=0;i<n;i++)
            dst[i].r /= n;
    }
}
inline lli manacher(char* sou,int len) {
    static char tp[maxn];
    static int p[maxn],mx,id;
    lli ret = 0;
    tp[0] = '$' , tp[1] = '#';
    for(int i=0;i<len;i++)
        tp[(i+1)<<1] = sou[i] , tp[((i+1)<<1)+1] = '#';
    len = ( len << 1 ) + 1;
    //puts(tp);
    for(int i=1;i<len;i++) {
        if( i < mx ) p[i] = min( mx - i , p[ id * 2 - i ] );
        else p[i] = 1;
        while( tp[i+p[i]] == tp[i-p[i]] ) ++p[i];
        if( i + p[i] > mx ) mx = i + p[i] , id = i;
        ret += p[i] >> 1 , ret %= mod;
        //debug<<"i = "<<i<<"p = "<<p[i]<<endl;
    }
    return ret;
}

inline void initpows() {
    *pows = 1;
    for(int i=1;i<maxn;i++)
        pows[i] = pows[i-1] * 2 % mod;
}
int main() {
    scanf("%s",in) , n = strlen(in);
    ans = mod - manacher(in,n);
    while( len < n ) len <<= 1;
    len <<= 1;
    for(int t=0;t<2;t++) {
        for(int i=0;i<len;i++)
            sou[i] = Comp( in[i] == 'a' + t );
        FFT(sou,len,1);
        for(int i=0;i<len;i++)
            dst[i] = dst[i] + sou[i] * sou[i];
    }
    FFT(dst,len,-1);
    initpows();
    for(int i=0;i<len;i++) {
        int t = ( dst[i].r + 0.1 );
        t = ( t + 1 ) >> 1;
        ans += pows[t] - 1;
        ans %= mod;
    }
    ans = ( ans % mod + mod ) % mod;
    printf("%lld\n",ans);
    return 0;
}
