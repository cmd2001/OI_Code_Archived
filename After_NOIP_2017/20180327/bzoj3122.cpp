#include<cstdio>
#include<cmath>
#include<map>
typedef long long int lli;
using namespace std;

lli mod;

struct Poly {
    lli k,b;
    inline Poly inter(const Poly &t) {
        return (Poly){t.k*k%mod,(t.b*k%mod+b)%mod};
    }
    inline lli ite(const lli &x) {
        return ( k * x % mod + b ) % mod;
    }
}now,trans,sqr;

inline lli exgcd(lli a,lli b,lli &x,lli &y) {
    if( !b ) {
        x = 1 , y = 0;
        return a;
    }
    lli ret = exgcd(b,a%b,y,x);
    y -= ( a / b ) * x;
    return ret;
}

inline lli getx(const Poly &p,const lli &t) {
    lli x,y,rit;
    exgcd(p.k,mod,x,y);
    rit = ( t - p.b + mod ) % mod , x = ( x % mod + mod ) % mod;
    return x * rit % mod;
}

inline lli bsgs(lli a,lli b,lli x,lli t) {
    if( !a && !b ) return x == t ? 1 : -1;
    map<lli,lli> mp;
    int sq = ( (double) sqrt(mod) + 0.5 ) + 1;
    sqr = now = (Poly){1,0} , trans = (Poly){a,b};
    for(int i=1;i<=sq;i++) {
        if( mp.find(x) == mp.end() ) mp[x] = i;
        x = trans.ite(x);
    }
    for(int i=1;i<=sq;i++) sqr = trans.inter(sqr);
    for(int i=0;i<=sq;i++) {
        lli tx = getx(now,t);
        if( mp.find(tx) != mp.end() ) return mp[tx] + i * sq;
        now = sqr.inter(now);
    }
    return -1;
}

int main() {
    static int T;
    static lli a,b,x,t;
    scanf("%d",&T);
    while(T--) {
        scanf("%lld%lld%lld%lld%lld",&mod,&a,&b,&x,&t);
        printf("%lld\n",bsgs(a,b,x,t));
    }
    return 0;
}

