#include<cstdio>
#include<algorithm>
#include<cmath>
#define bool unsigned char
#define debug cout
typedef long long int lli;
const int maxn=4e6+1e2,maxb=2e3+1e2;
const int mod=1e9+7;

lli phi[maxn];
int n,m;

inline lli fastpow(lli base,int tim) {
    lli ret = 1; base %= mod;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline int gcd(int x,int y) {
    register int t;
    while( ( t = x % y ) ) x = y , y = t;
    return y;
}

namespace Pre {
    inline void sieve() {
        static int prime[maxn],cnt;
        static bool vis[maxn];
        phi[1] = 1;
        for(int i=2;i<=n;i++) {
            if( !vis[i] ) prime[++cnt] = i , phi[i] = i - 1;
            for(int j=1;j<=cnt&&(lli)i*prime[j]<=n;j++) {
                const int tar = i * prime[j];
                vis[tar] = 1;
                if( i % prime[j] ) phi[tar] = phi[i] * ( prime[j] - 1 );
                else {
                    phi[tar] = phi[i] * prime[j];
                    break;
                }
            }
        }
        for(int i=1;i<=n;i++) phi[i] = ( phi[i] * i % mod * i % mod + phi[i-1] ) % mod;
    }
}

struct BlockedArrary {
    lli dat[maxn],sumins[maxn],blk[maxb],sumblk[maxb];
    int bel[maxn],st[maxb],ed[maxb],blksiz,cnt;
    
    inline lli query(int pos) {
        return pos ? ( sumblk[bel[pos]-1] + sumins[pos] ) % mod : 0;
    }
    inline void update(int pos,lli val) {
        dat[pos] = val;
        int id = bel[pos] , l = st[id] , r = ed[id];
        sumins[l] = dat[l]; for(int i=std::max(pos,l+1);i<=r;i++) sumins[i] = ( sumins[i-1] + dat[i] ) % mod;
        blk[id] = sumins[r]; for(int i=id;i<=cnt;i++) sumblk[i] = ( sumblk[i-1] + blk[i] ) % mod;
    }
    inline void init() {
        for(int i=1;i<=n;i++) dat[i] = (lli) i * i % mod;
        blksiz = std::sqrt(n);
        for(int l=1,r;l<=n;l=r+1) {
            r = std::min( l + blksiz - 1 , n ) , ++cnt , st[cnt] = l , ed[cnt] = r , sumins[l] = dat[l];
            for(int i=l;i<=r;i++) bel[i] = cnt;
            for(int i=l+1;i<=r;i++) sumins[i] = ( sumins[i-1] + dat[i] ) % mod;
            sumblk[cnt] = ( sumblk[cnt-1] + ( blk[cnt] = sumins[r] ) ) % mod;
        }
    }
}ba;

inline void update(int a,int b,lli d) {
    int g = gcd(a,b);
    lli tv = d % mod * fastpow((lli)a*b/g/g,mod-2) % mod;
    ba.update(g,tv);
}

inline lli query(int k) {
    lli ret = 0;
    for(int i=1,j;i<=k;i=j+1) {
        j = k / ( k / i );
        ret = ( ret + ( ba.query(j) - ba.query(i-1) + mod ) % mod * phi[k/i] % mod ) % mod;
    }
    return ret;
}

int main() {
    static int a,b,k;
    static lli x;
    scanf("%d%d",&m,&n) , Pre::sieve() , ba.init();
    while(m--) scanf("%d%d%lld%d",&a,&b,&x,&k) , update(a,b,x) , printf("%lld\n",query(k));
    return 0;
}

