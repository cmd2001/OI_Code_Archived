#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=262145;
const double pi = acos(-1.0);

struct Comp {
    double r,i;
    Comp() {}
    Comp(double rr,double ii=0) { r = rr , i = ii ; };
    Comp(int rr) { r = rr , i = 0 ; }
    friend Comp operator + (const Comp &a,const Comp &b) { return Comp(a.r+b.r,a.i+b.i); }
    friend Comp operator - (const Comp &a,const Comp &b) { return Comp(a.r-b.r,a.i-b.i); }
    friend Comp operator * (const Comp &a,const Comp &b) { return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r); }
}x[maxn],y[maxn];

inline void FFT(Comp* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap( dst[i] ,dst[j] );
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
                dst[st+pos+h] = u - v;
                w = w * per;
            }
        }
    }
    if( !~ope ) for(int i=0;i<n;i++) dst[i].r /= n;
}

int main() {
    static int n,len=1;
    scanf("%d",&n);
    for(int i=0,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        x[i] = Comp(a) , y[n-i-1] = Comp(b);
    }
    while( len <= n + n ) len <<= 1;
    FFT(x,len,1) , FFT(y,len,1);
    for(int i=0;i<len;i++) x[i] = x[i] * y[i];
    FFT(x,len,-1);
    for(int i=n-1,p;i<(n<<1)-1;i++) {
        p = x[i].r + 0.2;
        printf("%d\n",p);
    }
    return 0;
}
