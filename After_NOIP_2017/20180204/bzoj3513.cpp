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

struct Comp {
    double r,i;
    Comp() {}
    Comp(double rr,double ii) { r = rr , i = ii; }
    Comp(double rr) { r = rr , i = 0; }
    Comp(lli rr) { r = rr , i = 0; }
    friend Comp operator + (const Comp &a,const Comp &b) { return Comp(a.r+b.r,a.i+b.i); }
    friend Comp operator - (const Comp &a,const Comp &b) { return Comp(a.r-b.r,a.i-b.i); }
    friend Comp operator * (const Comp &a,const Comp &b) { return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r); }
    friend Comp operator *= (Comp &a,const Comp &b) {
        return a = a * b;
    }
}mul[maxn];
lli sig[maxn],muled[maxn],full,ans;
int in[maxn],n,mx,len;

inline void FFT(Comp* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        const Comp per = Comp( cos( pi * ope / h ) , sin( pi * ope / h ) );
        for(int st=0;st<n;st+=len) {
            Comp w = Comp( 1.0 , 0.0 );
            for(int pos=0;pos<h;pos++) {
                const Comp u = dst[st+pos] , v = dst[st+pos+h] * w;
                dst[st+pos] = u + v ,
                dst[st+pos+h] = u - v  ,
                w *= per;
            }
        }
    }
    if( !~ope ) {
        for(int i=0;i<n;i++)
            dst[i].r /= n;
    }
}
inline lli c(lli n) {
    return n *( n - 1 ) * ( n - 2 ) / 6; 
}
inline void print(lli ans,lli full) {
    long double p = (long double) ans / full;
    printf("%0.7Lf\n",p);
}
inline void init() {
    memset(mul,0,sizeof(mul)) , memset(sig,0,sizeof(sig));
    memset(in,0,sizeof(in)) , n = mx = 0 , len = 1;
}
int main() {
    static int T;
    scanf("%d",&T);
    while( T-- ) {
        init();
        scanf("%d",&n) , full = ans = c(n);
        for(int i=1;i<=n;i++)
            scanf("%d",in+i) , ++sig[in[i]] , mx = max( mx , in[i] );
        while( len <= ( mx << 1 ) ) len <<= 1;
        for(int i=0;i<len;i++)
            mul[i] = Comp( sig[i] );
        FFT(mul,len,1);
        for(int i=0;i<len;i++) mul[i] *= mul[i];
        FFT(mul,len,-1);
        for(int i=0;i<len;i++) muled[i] = (lli)(mul[i].r+0.20);
        for(int i=0;i<=mx;i++) muled[i<<1] -= sig[i];
        for(int i=0;i<len;i++) muled[i] = muled[i-1] + ( muled[i] >> 1 );
        for(int i=1;i<=n;i++) ans -= muled[in[i]];
        print(ans,full);
    }
    return 0;
}


