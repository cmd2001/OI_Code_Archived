#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
typedef long long int lli;
const int maxn=131073,lim=5e4;
const double pi = acos(-1.0);
const double eps = 5e-1;

int ia[maxn],ib[maxn];
lli ans[maxn];

struct Complex {
    double r,i;
    friend Complex operator + (const Complex &a,const Complex &b) { return (Complex){a.r+b.r,a.i+b.i}; }
    friend Complex operator - (const Complex &a,const Complex &b) { return (Complex){a.r-b.r,a.i-b.i}; }
    friend Complex operator * (const Complex &a,const Complex &b) { return (Complex){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r}; }
}a[maxn],b[maxn],c[maxn];

inline void FFT(Complex* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
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
inline void mul(Complex* dst,Complex* sa,Complex* sb,int len) {
    FFT(sa,len,1) , FFT(sb,len,1);
    for(int i=0;i<len;i++) dst[i] = sa[i] * sb[i];
    FFT(dst,len,-1);
}

inline void solve(int l,int r) { // assert l <= r;
    const int mid = ( l + r ) >> 1;

    int len,ll=mid-l+1;
    for(len=1;len<=r-l+1;len<<=1) ;

    memset(a,0,sizeof(Complex)*len) , memset(b,0,sizeof(Complex)*len);
    for(int i=l;i<=mid;i++) a[i-l] = (Complex){(double)ia[i],0.0};
    for(int i=mid+1;i<=r;i++) b[i-mid-1] = (Complex){(double)ib[i],0.0};
    mul(c,a,b,len);
    for(int i=0;i<=r-l+1;i++) ans[i+l+mid+1] += (lli)(c[i].r+eps);

    memset(a,0,sizeof(Complex)*len) , memset(b,0,sizeof(Complex)*len);
    for(int i=mid+1;i<=r;i++) a[i-mid-1] = (Complex){(double)ia[i],0.0};
    for(int i=l;i<=mid;i++) b[ll-(i-l)] = (Complex){(double)ib[i],0.0};
    mul(c,a,b,len);
    for(int i=0;i<=r-l+1;i++) ans[i] += (lli)(c[i].r+eps);

    if( l != r ) solve(l,mid) , solve(mid+1,r);
}

inline void reset() {
    memset(ia,0,sizeof(ia)) , memset(ib,0,sizeof(ib)) , memset(ans,0,sizeof(ans));
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int T,n,m,q,t,mxlen;
    T = getint();
    while(T--) {
        n = getint() , m = getint() , q = getint() , reset() , mxlen = 0;
        while(n--) ++ia[t=getint()] , mxlen = std::max(mxlen,t);
        while(m--) ++ib[t=getint()] , mxlen = std::max(mxlen,t);
        for(int i=0;i<=mxlen;i++) ans[0] += (lli) ia[i] * ib[i];
        solve(0,mxlen);
        while(q--) printf("%lld\n",ans[getint()]);
    }
    return 0;
}
