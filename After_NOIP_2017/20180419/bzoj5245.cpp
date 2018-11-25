#include<cstdio>
#include<bitset>
typedef long long int lli;
typedef std::bitset<4680> bs;
using namespace std;
const int maxn=5e4+1e2;
const int mod=1e9+7;

int in[maxn];
int prime[maxn],dv[maxn],cnt;
lli inv[maxn];

inline bs getdivide(int x) { // alert that x may be 0 .
    bs ret = bs(0);
    while( x > 1 ) ret[dv[x]] = 1 , x /= prime[dv[x]];
    return ret;
}

struct SegmentTree {
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],cnt;
    lli sum[maxn<<2],mul[maxn<<2];
    bs sta[maxn<<2];
    
    SegmentTree() { cnt = 1 ; }
    
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) {
            sta[pos] = getdivide(in[ll]) , mul[pos] = sum[pos] = in[ll];
            return;
        } const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        sta[pos] = sta[lson[pos]] | sta[rson[pos]] , mul[pos] = mul[lson[pos]] * mul[rson[pos]] % mod , sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline void update(int pos,const int &tar,const int &x) {
        if( l[pos] == r[pos] ) {
            sta[pos] = getdivide(x) , mul[pos] = sum[pos] = x;
            return;
        } const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) update(lson[pos],tar,x);
        else update(rson[pos],tar,x);
        sta[pos] = sta[lson[pos]] | sta[rson[pos]] , mul[pos] = mul[lson[pos]] * mul[rson[pos]] % mod , sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline lli querysum(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return 0;
        if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
        return querysum(lson[pos],ll,rr) + querysum(rson[pos],ll,rr);
    }
    inline lli querymul(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return 1;
        if( ll <= l[pos] && r[pos] <= rr ) return mul[pos];
        return querymul(lson[pos],ll,rr) * querymul(rson[pos],ll,rr) % mod;
    }
    inline bs querysta(int pos,const int &ll,const int &rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return sta[pos];
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return querysta(lson[pos],ll,rr);
        else if( ll > mid ) return querysta(rson[pos],ll,rr);
        return querysta(lson[pos],ll,rr) | querysta(rson[pos],ll,rr);
    }
}sgt;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

inline void sieve() {
    static const int lim=4.5e4;
    static bool vis[maxn];
    static lli fac[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , dv[i] = cnt;
        for(int j=1,tar;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            tar = i * prime[j] , vis[tar] = 1 , dv[tar] = j;
            if( ! ( i % prime[j] ) ) break;
        }
    }
    *fac = 1;
    for(int i=1;i<=lim;i++) fac[i] = fac[i-1] * i % mod;
    inv[lim] = fastpow(fac[lim],mod-2);
    for(int i=lim;i;i--) inv[i-1] = inv[i] * i % mod;
    for(int i=1;i<=lim;i++) inv[i] = inv[i] * fac[i-1] % mod;
}

inline lli forcephi(lli x) {
    lli ret = x;
    for(int i=1;i<=cnt&&(lli)prime[i]*prime[i]<=x;i++) if( ! ( x % prime[i] ) ) {
        ret = ret / prime[i] * ( prime[i] - 1 );
        while( ! ( x % prime[i] ) ) x /= prime[i];
    }
    if( x != 1 ) ret = ret / x * ( x - 1 );
    return ret % mod;
}

inline lli calcphi(lli x,const bs &b) {
    for(int i=b._Find_next(0);i<=cnt;i=b._Find_next(i)) x = x * inv[prime[i]] % mod * ( prime[i] - 1 ) % mod;
    return x;
}

int main() {
    static int n,q;
    scanf("%d%d",&n,&q) , sieve();
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    sgt.build(1,1,n);
    for(int i=1,o,l,r;i<=q;i++) {
        scanf("%d%d%d",&o,&l,&r);
        if( o == 0 ) sgt.update(1,l,r);
        else if( o == 1 ) printf("%lld\n",forcephi(sgt.querysum(1,l,r)));
        else if( o == 2 ) printf("%lld\n",calcphi(sgt.querymul(1,l,r),sgt.querysta(1,l,r)));
    }
    return 0;
}
