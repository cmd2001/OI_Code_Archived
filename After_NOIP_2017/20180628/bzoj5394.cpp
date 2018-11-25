#include<cstdio>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=5e5+1e2,maxe=2e7+1e2,lim=2e7;

int n;
struct BinaryIndexTree {
    lli dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,const lli &x) {
        while( pos <= n ) dat[pos] += x , pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = 0;
        while(pos) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}bit;

int phi[maxe];

inline void sieve() {
    static int prime[maxe/10],cnt;
    static unsigned char vis[maxe];
    phi[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , phi[i] = i - 1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            const lli tar = i * prime[j];
            vis[tar] = 1;
            if( i % prime[j] ) phi[tar] = phi[i] * ( prime[j] - 1 );
            else {
                phi[tar] = phi[i] * prime[j];
                break;
            }
        }
    }
}

inline lli fastpow(lli base,lli tim,int mod,bool &abo) { // assert tim != 0 .
    static lli t;
    lli ret = 1; abo = 0;
    if( base >= mod ) base %= mod , abo = 1;
    while(tim) {
        if( tim & 1 ) {
            t = base * ret;
            if( t >= mod ) t %= mod , abo = 1;
            ret = t;
        }
        if( tim >>= 1 ) {
            t = base * base;
            if( t >= mod ) t %= mod , abo = 1;
            base = t;
        }
    }
    if( ret >= mod ) ret %= mod , abo = 1; // mod may be 1 .
    return ret;
}
inline lli calc(int pos,int rit,int mod,bool &prvabo) {
    if( pos == rit ) return fastpow(bit.query(pos),1,mod,prvabo);
    bool abo; lli t = calc(pos+1,rit,phi[mod],abo);
    return fastpow(bit.query(pos),t+abo*phi[mod],mod,prvabo);
}

namespace IO {
    inline char nextchar() {
        static const int BS = 1 << 21;
        static char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? -1 : *st++;
    }
    inline int getint() {
        int ret = 0 , fix = 1;
        char ch;
        while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret * fix;
    }
}
using IO::getint;

int main() {
    static int m;
    static bool fake;
    n = getint() , m = getint() , sieve();
    for(int i=1,x,last=0;i<=n;i++) x = getint() , bit.update(i,x-last) , last = x;
    for(int i=1,o,l,r,x;i<=m;i++) {
        o = getint() , l = getint() , r = getint() , x = getint();
        if( o == 1 ) bit.update(l,x) , bit.update(r+1,-x);
        else printf("%lld\n",calc(l,std::min(r,l+30),x,fake));
    }
    return 0;
}
