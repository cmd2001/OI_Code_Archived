#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<tr1/unordered_map>
#include<cmath>
#define debug cout
typedef long long int lli;
using namespace std;
using namespace tr1;
const int maxn=1e5+1e2;

lli dvs[maxn],cnt;
lli k,a,p,g,n,m;

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
inline void getdvs(lli x) {
    for(lli i=2;i*i<=x;i++) if( ! ( x % i ) ) {
        dvs[++cnt] = i;
        while( ! ( x % i ) ) x /= i;
    }
    if( x != 1 ) dvs[++cnt] = x;
}
inline lli getroot() {
    lli ret = 1;
    bool fail;
    while( ++ret < p ) {
        fail = 0;
        for(lli i=1;i<=cnt;i++) if( fastpow(ret,(p-1)/dvs[i],p) == 1 ) fail = 1;
        if( !fail ) return ret;
    }
    throw "There is no primary root !";
}
inline lli BSGS(lli base,lli tar,lli mod) {
    tr1::unordered_map<lli,lli> mp;
    lli sq = sqrt(mod) + 1 , cur = 1 , giant = 1;
    for(lli pw=0;pw<sq;pw++) {
        if( mp.find(cur) == mp.end() ) mp[cur] = pw;
        cur = cur * base % mod; 
    } // now cur = base ^ sq .
    for(lli i=0;i<=sq;i++) {
        lli ned = tar * fastpow(giant,mod-2,mod) % mod;
        if( mp.find(ned) != mp.end() ) return i * sq + mp[ned];
        giant = giant * cur % mod;
    }
    throw "No solution !";
}

int main() {
    static lli ans[maxn],anslen;
    scanf("%lld%lld%lld",&p,&k,&a);
    if( !a ) return puts("1\n0"),0;
    if( p == 2 ) return puts("1\n1"),0;
    getdvs(p-1) , g = getroot() , m = BSGS(g,a,p);
    lli x,y,gcd=exgcd(k,p-1,x,y);
    if( m % gcd ) return puts("0"),0;
    lli step = ( p - 1 ) / gcd;
    x = ( x * ( m / gcd ) % step + step ) % step;
    while( x < p - 1 ) ans[++anslen] = fastpow(g,x,p) , x += step;
    if(!anslen) return puts("0"),0;
    std::sort(ans+1,ans+1+anslen) , printf("%lld\n",anslen);
    for(int i=1;i<=anslen;i++) printf("%lld\n",ans[i]);
    return 0;
}
