#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
typedef long long int lli;
using namespace std;
const int mod=1e9+7;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void sube(int &dst,const int &x) {
    if( ( dst -= x ) < 0 ) dst += mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}

struct Interval {
    int xs[11],ys[11],ps[11],cnt;
    inline void insert(const int &x,const int &y) {
        xs[++cnt] = x , ys[cnt] = y;
    }
    inline void init() {
        for(int i=1;i<=cnt;i++) {
            ps[i] = 1;
            for(int j=1;j<=cnt;j++) if( j != i ) mule(ps[i],sub(xs[i],xs[j]));
            ps[i] = fastpow(ps[i],mod-2);
        }
    }
    inline int calc(const int &x) {
        int ret = 0;
        for(int i=1;i<=cnt;i++) {
            int pi = 1;
            for(int j=1;j<=cnt;j++) if( j != i ) mule(pi,sub(x,xs[j]));
            adde(ret,mul(mul(pi,ps[i]),ys[i]));
        }
        return ret;
    }
    inline void reset() {
        cnt = 0;
    }
}s,f;

lli m;
int sq,ans;

inline void inits() {
    const int m = ::m % mod;
    for(int i=m,su;i>m-4;i--) {
        su = 0;
        for(int j=i;j<=m;j++) adde(su,mul(j,sub((m+1)%mod,j)));
        s.insert(i,su);
    }
    s.init();
}
inline void initf(int x) {
    f.reset();
    for(int i=1,su=0;i<=8;i++) adde(su,s.calc(((lli)x*x+i*i)%mod)) , f.insert(i,su);
    f.init();
}

int main() {
    scanf("%lld",&m) , inits() , sq = sqrt(m);
    for(int i=0;i<=sq;i++) {
        if( (lli) i * i + 8 * 8 <= m ) initf(i) , adde(ans,f.calc((lli)sqrt(m-(lli)i*i)%mod));
        else {
            int t = sqrt(m-(lli)i*i);
            for(int j=1;j<=t;j++) adde(ans,s.calc(((lli)i*i+j*j)%mod));
        }
    }
    mule(ans,4) , adde(ans,s.calc(0)) , printf("%d\n",ans);
    return 0;
}

