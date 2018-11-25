#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long int lli;
const int maxn=1048579;
const double pi = acos(-1.0);

char in[maxn];

struct Complex {
    double r,i;
    friend Complex operator + (const Complex &a,const Complex &b) { return (Complex){a.r+b.r,a.i+b.i}; }
    friend Complex operator - (const Complex &a,const Complex &b) { return (Complex){a.r-b.r,a.i-b.i}; }
    friend Complex operator * (const Complex &a,const Complex &b) { return (Complex){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r}; }
}a[maxn],b[maxn],c[maxn];
 
inline void FFT(Complex* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        const Complex per = (Complex){cos(pi*tpe/h),sin(pi*tpe/h)};
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

int main() {
    static int n,len;
    static lli ans;
    scanf("%s",in) , n = strlen(in);
    for(len=1;len<=n<<1;len<<=1) ;

    memset(a,0,sizeof(a)) , memset(b,0,sizeof(b));
    for(int i=0;i<n;i++) a[i] = (Complex){in[i]=='0',0} , b[i] = (Complex){in[i]=='1',0};
    reverse(b,b+n) , FFT(a,len,1) , FFT(b,len,1);
    for(int i=0;i<len;i++) c[i] = a[i] * b[i];

    memset(a,0,sizeof(a)) , memset(b,0,sizeof(b));
    for(int i=0;i<n;i++) a[i] = (Complex){in[i]=='1',0}, b[i] = (Complex){in[i]=='0',0};
    reverse(b,b+n) , FFT(a,len,1) , FFT(b,len,1);
    for(int i=0;i<len;i++) c[i] = c[i] + a[i] * b[i];

    FFT(c,len,-1) , ans = (lli) n * n;

    for(int i=1;i<n;i++) {
        bool can = 1;
        for(int j=i;j<=n;j+=i) if( (int) ( c[n-j-1].r+0.5 ) ) { can = 0; break; }
        if(can) ans ^= (lli) ( n - i ) * ( n - i );
    }

    printf("%lld\n",ans);
    return 0;
}
