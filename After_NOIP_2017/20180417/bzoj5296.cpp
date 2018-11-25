#include<cstdio>
#include<cmath>
#include<tr1/unordered_map>
typedef long long int lli;
using namespace std;
using namespace tr1;

lli sq,psq;
unordered_map<lli,lli> mp;

inline lli fastpow(lli base,lli tim,lli mod) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 )  ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

inline lli BSGS(lli A,lli p) {
    lli now = 1 , fd;
    for(int i=0;i<=sq;i++) {
        fd = A * fastpow(now,p-2,p) % p;
        if( mp.find(fd) != mp.end() ) return i * sq + mp[fd];
        now = now * psq % p;
    }
    throw "It shouldn't be here";
}

inline void pre(lli g,lli p) {
    sq = sqrt(p) + 1;
    lli now = 1;
    for(int i=0;i<=sq;i++) {
        if( mp.find(now) == mp.end() ) mp[now] = i;
        if( i != sq ) now = now * g % p ;
    }
    psq = now;
}

int main() {
    static int T;
    static lli g,p,A,B,a,b,ans;
    scanf("%lld%lld%d",&g,&p,&T) , pre(g,p);
    while(T--) {
        scanf("%lld%lld",&A,&B) , a = BSGS(A,p) , b = BSGS(B,p);
        ans = fastpow(g,a*b,p) , printf("%lld\n",ans);
    }
    return 0;
}