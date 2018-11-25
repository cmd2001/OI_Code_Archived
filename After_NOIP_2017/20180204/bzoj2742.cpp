#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e2+1e1,maxm=2e7+1e2;
const int mod=1e9+7;

struct Number {
    int a,b,f;
    friend bool operator < (const Number &a,const Number &b) {
        if( a.f != b.f ) return a.f < b.f;
        if( !~a.f ) return (double)a.a/a.b > (double)b.a/b.b;
        return (double)a.a/a.b < (double)b.a/b.b;
    }
    friend bool operator == (const Number &a,const Number &b) {
        return a.a == b.a && a.b == b.b && a.f == b.f;
    }
    inline void print() {
        if( !~f ) putchar('-');
        if( b == 1 ) printf("%d",a);
        else printf("%d/%d",a,b);
    }
}nums[maxm>>4];
int in[maxn],n,len;
int dva[maxm>>4],dvb[maxm>>4],la,lb;

inline int fastpow(int base,int tim,int mod) {
    lli now = base , ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = ret * now % mod;
        if( tim >>=1 ) now = now * now % mod;
    }
    return ret;
}
inline int gcd(int a,int b) {
    if( ! ( a && b ) ) return a | b;
    register int t;
    while( t = a % b )
        a = b , b = t;
    return b;
}
inline void check(int a,int b,int f) {
    static lli pa[maxn],pb[maxn];
    lli rb=fastpow(b,mod-2,mod);
    *pa = *pb = 1;
    for(int i=1;i<=n;i++) {
        pa[i] = pa[i-1] * a * f % mod ,
        pb[i] = pb[i-1] * rb % mod;
    }
    lli ret = 0;
    for(int i=0;i<=n;i++) {
        ret = ( ret + in[i] * pa[i] % mod * pb[i] % mod ) % mod;
    }
    if( !ret ) nums[++len] = (Number){a,b,f};
}
inline void divi(int x,int* dst,int& len) {
    x = x > 0 ? x : -x;
    if( !x ) dst[++len] = 1;
    for(int i=1;i*i<=x;i++)
        if( ! ( x % i ) ) {
            dst[++len] = i;
            if( i * i != x ) dst[++len] = x / i;
        }
}
inline void printans() {
    sort(nums+1,nums+1+len);
    len = unique(nums+1,nums+1+len) - nums - 1;
    printf("%d\n",len);
    for(int i=1;i<=len;i++)
        nums[i].print() , putchar('\n');
}

int main() {
    scanf("%d",&n);
    for(int i=0;i<=n;i++) scanf("%d",in+i);
    for(int i=0;i<n;i++)
        if( in[i] ) {
            divi(in[i],dva,la);
            if( i ) nums[++len] = (Number){0,1,1};
            break;
        }
    divi(in[n],dvb,lb);
    for(int i=1;i<=la;i++)
        for(int j=1;j<=lb;j++)
            if( gcd(dva[i],dvb[j]) == 1 ) {
                check(dva[i],dvb[j],1) ,
                check(dva[i],dvb[j],-1);
            }
    printans();
    return 0;
}

