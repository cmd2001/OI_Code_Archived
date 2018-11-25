#include<cstdio>
typedef long long int lli;
const int maxn=2e5+1e2;
const int mod=998244353;

lli fac[maxn],inv[maxn],ans,su;
int n;

inline lli c(int n,int m) {
    if( n < m ) return 0;
    return fac[n] * inv[m] % mod * inv[n-m] % mod;
}
inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline void init() {
    *fac = 1; for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i % mod;
    inv[n] = fastpow(fac[n],mod-2); for(int i=n;i;i--) inv[i-1] = inv[i] * i % mod;
}

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1],siz[maxn];
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void pre(int pos,int fa) {
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) pre(t[at],pos) , siz[pos] += siz[t[at]];
    }
    inline void dfs(int pos,int fa,int k) {
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
            ans = ( ans + ( ( su - c(siz[t[at]],k) - c(n-siz[t[at]],k) ) % mod + mod ) % mod * l[at] % mod ) % mod;
            dfs(t[at],pos,k);
        }
    }
}

int main() {
    static int q;
    freopen("orient.in","r",stdin);
    freopen("orient.out","w",stdout);
    scanf("%d%d",&n,&q) , init();
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , Tree::addedge(a,b,l<<1);
    Tree::pre(1,-1);
    for(int i=1,k;i<=q;i++) {
        scanf("%d",&k) , ans = 0 , su = c(n,k);
        Tree::dfs(1,-1,k) , printf("%lld\n",ans*fastpow(su,mod-2)%mod);
    }
    fclose(stdout);
    return 0;
}
