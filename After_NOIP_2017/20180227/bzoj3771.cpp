#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=131073;
const double pi = acos(-1.0);

struct Complex {
    double r,i;
    Complex() {}
    Complex(long long rr) { r = rr , i = 0; }
    Complex(double rr,double ii) { r = rr , i = ii; }
    friend Complex operator + (const Complex &a,const Complex &b) { return Complex(a.r+b.r,a.i+b.i); }
    friend Complex operator - (const Complex &a,const Complex &b) { return Complex(a.r-b.r,a.i-b.i); }
    friend Complex operator * (const Complex &a,const Complex &b) { return Complex(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r); }
    Complex operator += (const Complex &b) { return *this = *this + b; }
    Complex operator *= (const Complex &b) { return *this = *this * b; }
}a[maxn],b[maxn],c[maxn],tp[maxn];

int in[maxn],len=1;

inline void FFT(Complex* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap( dst[i] ,dst[j] );
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        const Complex per = Complex(cos(pi*tpe/h),sin(pi*tpe/h));
        for(int st=0;st<n;st+=len) {
            Complex w = Complex(1.0,0.0);
            for(int pos=0;pos<h;pos++) {
                const Complex u = dst[st+pos] , v = dst[st+pos+h] * w;
                dst[st+pos] = u + v ,
                dst[st+pos+h] = u - v ,
                w *= per;
            }
        }
    }
    if( !~tpe ) for(int i=0;i<n;i++) dst[i].r /= n;
}

int main() {
    static int n,mx;
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x) , ++in[x] , mx = max( mx , 3 * x );
    }
    while( len <= mx ) len <<= 1;
    for(int i=0,lim=mx/3;i<=lim;i++) {
        a[i] = Complex(in[i]) ,
        b[i*2] = Complex(in[i]*in[i]) ,
        c[i*3] = Complex((long long)in[i]*in[i]*in[i]);
    }
    FFT(a,len,1) , FFT(b,len,1) , FFT(c,len,1);
    Complex mul3 = Complex(3) , mul2 = Complex(2) , inv2 = Complex(1.0/2.0,0) , inv6 = Complex(1.0/6.0,0.0);
    for(int i=0;i<=len;i++) {
        tp[i] = a[i] + ( a[i] * a[i] - b[i] ) * inv2 + ( a[i] * a[i] * a[i] - mul3 * a[i] * b[i] + mul2 * c[i] ) * inv6;
    }
    FFT(tp,len,-1);
    for(int i=0;i<len;i++) {
        const long long way = (long long) ( tp[i].r + 0.2 );
        if( way ) printf("%d %lld\n",i,way);
    }
    return 0;
}
