#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=2e4+1e2,maxk=25;
const int mod=1e9+7;


lli c[maxk][maxk];
int n,k;

namespace Pre {
    lli fac[maxk],inv[maxk];
    inline lli fastpow(lli base,int tim) {
        lli ret = 1;
        while( tim ) {
            if( tim & 1 ) ret = ret * base % mod;
            if( tim >>= 1 ) base = base * base % mod;
        }
        return ret;
    }
    inline lli C(int n,int m) {
        return fac[n] * inv[m] % mod * inv[n-m] % mod;
    }
    inline void work() {
        *fac = 1;
        for(int i=1;i<=k;i++) fac[i] = fac[i-1] * i % mod;
        inv[k] = fastpow(fac[k],mod-2);
        for(int i=k;i;i--) inv[i-1] = inv[i] * i % mod;
        for(int i=0;i<=k;i++)
            for(int j=0;j<=i;j++)
                c[i][j] = C(i,j);
    }
}

struct Poly {
    lli dat[maxk];
    Poly() {
        memset(dat,0,sizeof(dat));
    }
    lli& operator [] (const int &x) {
        return dat[x];
    }
    const lli& operator [] (const int &x) const {
        return dat[x];
    }
    friend Poly operator + (const Poly &a,const Poly &b) {
        Poly ret;
        for(int i=0;i<=k;i++)
            ret[i] = ( a[i] + b[i] ) % mod;
        return ret;
    }
    friend Poly operator - (const Poly &a,const Poly &b) {
        Poly ret;
        for(int i=0;i<=k;i++)
            ret[i] = ( a[i] - b[i] + mod ) % mod;
        return ret;
    }
    friend Poly operator + (const Poly &a,lli x) {
        Poly ret; x = ( x + mod ) % mod;
        static lli pows[maxk];
        *pows = 1;
        for(int i=1;i<=k;i++) pows[i] = pows[i-1] * x % mod;
        for(int i=k;~i;i--) {
            for(int j=i;~j;j--)
                ret[i] += a[j] * pows[i-j] % mod * c[i][j] % mod , ret[i] %= mod;
        }
        return ret;
    }
    inline void init() {
        for(int i=0;i<=k;i++) dat[i] = 1;
    }
}sson[maxn],sfa[maxn],f[maxn];
// sson is dis of points in subtree to pos .

int s[maxn],t[maxn<<1],nxt[maxn<<1],fa[maxn],cnt;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfsson(int pos) {
    sson[pos].init();
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        fa[t[at]] = pos , dfsson(t[at]);
        sson[pos] = sson[pos] + ( sson[t[at]] + 1 ) ;
    }
}
inline void dfsfa(int pos) {
    if( fa[pos] ) {
        sfa[pos] = sfa[fa[pos]] + 1;
        Poly delta = sson[fa[pos]] - ( sson[pos] + 1 );
        sfa[pos] = sfa[pos] + ( delta + 1 );
    }
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfsfa(t[at]);
}
inline void getans() {
    for(int i=1;i<=n;i++) {
        Poly sum = sfa[i] + sson[i];
        printf("%lld\n",sum.dat[k]);
    }
    putchar('\n');
}

int main() {
    while( scanf("%d%d",&n,&k) == 2 ) {
        memset(s,0,sizeof(int)*(n+1)) , cnt = 0;
        Pre::work();
        for(int i=1,a,b;i<n;i++) {
            scanf("%d%d",&a,&b) ,
            addedge(a,b) , addedge(b,a);
        }
        dfsson(1) , dfsfa(1);
        getans();
    }
    return 0;
}
