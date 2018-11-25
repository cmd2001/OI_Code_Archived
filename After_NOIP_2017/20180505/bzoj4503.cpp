#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
const int maxn=262145;
const double pi = std::acos(-1.0);

char ina[maxn],inb[maxn];
int ans[maxn],su;

struct Complex {
    double r,i;
    friend Complex operator + (const Complex &a,const Complex &b) { return (Complex){a.r+b.r,a.i+b.i}; }
    friend Complex operator - (const Complex &a,const Complex &b) { return (Complex){a.r-b.r,a.i-b.i}; }
    friend Complex operator * (const Complex &a,const Complex &b) { return (Complex){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r}; }
    friend Complex operator * (const Complex &a,const int &x) { return (Complex){a.r*x,a.i*x}; }
}a[maxn],a2[maxn],b[maxn],b2[maxn],b3[maxn],one[maxn],mul[maxn];

inline void FFT(Complex* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        const Complex per = (Complex){std::cos(pi*tpe/h),std::sin(pi*tpe/h)};
        for(int st=0;st<n;st+=len) {
            Complex w = (Complex){1.0,0.0};
            for(int pos=0;pos<h;pos++) {
                const Complex u = dst[st+pos] , v = dst[st+pos+h] * w;
                dst[st+pos] = u + v , dst[st+pos+h] = u - v , w = w * per;
            }
        }
    }
    if( !~tpe ) for(int i=0;i<n;i++) dst[i].r /= n;
}

inline void fix(char* s,const int &li) {
    for(int i=0;i<li;i++) s[i] = s[i] == '?' ? 0 : s[i] - 'a' + 1;
}
inline void cov(Complex* dst,const char* sou,const int &li) {
    for(int i=0;i<li;i++) dst[i] = (Complex){(double)sou[i],0.0};
}

int main() {
    static int la,lb,len;
    scanf("%s%s",ina,inb) , la = strlen(ina) , lb = strlen(inb);
    fix(ina,la) , fix(inb,lb) , std::reverse(inb,inb+lb) , cov(a,ina,la) , cov(b,inb,lb);
    for(len=1;len<=(la+lb);len<<=1) ;
    for(int i=0;i<len;i++) a2[i] = a[i] * a[i] , one[i] = (Complex){1.0,0.0};
    for(int i=0;i<len;i++) b2[i] = b[i] * b[i] , b3[i] = b2[i] * b[i];
    FFT(a,len,1) , FFT(a2,len,1) , FFT(b,len,1) , FFT(b2,len,1) , FFT(b3,len,1) , FFT(one,len,1);
    for(int i=0;i<len;i++) mul[i] = a2[i] * b[i] - ( a[i] * b2[i] * 2 ) + b3[i] * one[i];
    FFT(mul,len,-1);
    for(int i=0;i<len;i++) ans[i] = int(mul[i].r+0.4);
    for(int i=lb-1;i<la;i++) if( !ans[i] ) ++su;
    printf("%d\n",su);
    for(int i=lb-1;i<la;i++) if( !ans[i] ) printf("%d\n",i-lb+1);
    return 0;
}
