#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn = 2097153;
const double pi = acos(-1.0);


struct Complex {
    double r,i;
    friend Complex operator + (const Complex &a,const Complex &b) {
        return (Complex){a.r+b.r,a.i+b.i};
    }
    friend Complex operator - (const Complex &a,const Complex &b) {
        return (Complex){a.r-b.r,a.i-b.i};
    }
    friend Complex operator * (const Complex &a,const Complex &b) {
        return (Complex){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r};
    }
}a[maxn],b[maxn];

inline void FFT(Complex* dst,const int &n,const int &tpe) {
    for(int i=0,j=0;i<n;i++) {
        if(i < j) swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1);
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        const Complex per = (Complex){cos(pi*tpe/h),sin(pi*tpe/h)};
        for(int st=0;st<n;st+=len) {
            Complex w = (Complex){1.0,0.0};
            for(int pos=0;pos<h;pos++) {
                const Complex u = dst[st+pos], v = dst[st+pos+h] * w;
                dst[st+pos] = u + v, dst[st+pos+h] = u - v, w = w * per;
            }
        }
    }
    if(!~tpe) for(int i=0;i<n;i++) dst[i].r /= n;
}

int main() {
    static int n,m,len;
    scanf("%d%d",&n,&m);
    for(len=1;len<=n+m;len<<=1) ;
    for(int i=0;i<=n;i++) scanf("%lf",&a[i].r);
    for(int i=0;i<=m;i++) scanf("%lf",&b[i].r);
    FFT(a,len,1), FFT(b,len,1);
    for(int i=0;i<len;i++) a[i] = a[i] * b[i];
    FFT(a,len,-1);
    for(int i=0;i<=n+m;i++) printf("%lld ",(long long)(a[i].r+0.5));
    puts("");
    return 0;
}

