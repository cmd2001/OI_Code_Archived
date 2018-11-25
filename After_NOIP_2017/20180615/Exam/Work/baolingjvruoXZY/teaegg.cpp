#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<tr1/unordered_map>
#include<cassert>
#define debug cout
typedef long long int lli;
using namespace std;
using namespace tr1;
const int maxn=5e5+1e2;

lli ans[maxn],anslen;
lli a,b,p,g;

inline bool isprime(lli x) {
    const lli sq = sqrt(x);
    for(lli i=2;i<=sq;i++) if( ! ( x % i ) ) return 0;
    return 1;
}

inline lli fastpow(lli base,lli tim,lli mod) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline lli exgcd(lli a,lli b,lli &x,lli &y) {
    if( !b ) return x = 1 , y = 0 , a;
    lli ret = exgcd(b,a%b,y,x);
    return y -= a / b * x , ret;
}

namespace BSGS {
    inline lli BSGS(lli a,lli b) {
        const lli sq = sqrt(p);
        unordered_map<lli,lli> mp;
        lli step = 1 , giant = 1;
        for(lli i=0;i<sq;i++) {
            if( mp.find(step) == mp.end() ) mp[step] = i;
            step = step * a % p;
        }
        for(lli i=0;i<=sq;i++) {
            const lli ned = b * fastpow(giant,p-2,p) % p;
            if( mp.find(ned) != mp.end() ) return sq * i + mp[ned];
            giant = giant * step % p;
        }
        assert(0);
    }
}

namespace GetPrimaryRoot {
    lli dvs[maxn],cnt;
    inline void cut(lli t) {
        const lli sq = sqrt(t);
        for(lli i=2;i<=sq;i++) {
            if( ! ( t % i ) ) {
                dvs[++cnt] = i;
                while( ! ( t % i ) ) t /= i;
            }
        }
        if( t != 1 ) dvs[++cnt] = t;
    }
    inline bool judge(lli x) {
        for(lli i=1;i<=cnt;i++) if( fastpow(x,(p-1)/dvs[i],p) == 1 ) return 0;
        return 1;
    }
    inline lli getroot() {
        for(lli i=1;i<p;i++) if( judge(i) ) return i;
        assert(0);
    }
}

int main() {
    static lli n,phi,x,y,gcd,step;
    freopen("teaegg.in","r",stdin);
    freopen("teaegg.out","w",stdout);
    scanf("%lld%lld%lld",&a,&b,&p) , p = isprime(p) ? p : 2;
    if( p == 2 ) return assert(b) , puts("1\n1") , 0;
    GetPrimaryRoot::cut(p-1) , g = GetPrimaryRoot::getroot() , n = BSGS::BSGS(g,b);
    phi = p - 1 , gcd = exgcd(a,phi,x,y);
    if( n % gcd ) return puts("0") , 0;
    step = phi / gcd , x = ( x % step + step ) % step , x = x * ( n / gcd ) % step;
    while( x < phi ) ans[++anslen] = fastpow(g,x,p) , x += step;
    if( !anslen ) return puts("0") , 0;
    sort(ans+1,ans+1+anslen) , printf("%lld\n",anslen);
    for(lli i=1;i<=anslen;i++) printf("%lld%c",ans[i],i!=anslen?' ':'\n');
    fclose(stdout);
    return 0;
}

