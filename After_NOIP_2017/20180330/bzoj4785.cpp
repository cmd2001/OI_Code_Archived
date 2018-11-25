#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=2e7+1e2;
const int mod=998244353;

int lson[maxe],rson[maxe],sum[maxe],cnt;
lli f[maxe],ans;
int root[maxn<<3],olson[maxn<<3],orson[maxn<<3];
int n;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline lli merge(const lli &x,const lli &y) {
    return ( x * y % mod + ( 1 - x + mod ) * ( 1 - y + mod ) % mod ) % mod;
}
inline void build(int pos,int l,int r) {
    static int cnt = 1;
    if( l == r ) return;
    const int mid = ( l + r ) >> 1;
    build(olson[pos]=++cnt,l,mid) , build(orson[pos]=++cnt,mid+1,r);
}
inline void update(int &pos,int l,int r,const int &ll,const int &rr,const lli &c) {
    if( !pos ) f[pos=++cnt] = 1;
    if( ll <= l && r <= rr ) return void(f[pos]=merge(f[pos],c));
    const int mid = ( l + r ) >> 1;
    if( rr <= mid ) update(lson[pos],l,mid,ll,rr,c);
    else if( ll > mid ) update(rson[pos],mid+1,r,ll,rr,c);
    else update(lson[pos],l,mid,ll,rr,c) , update(rson[pos],mid+1,r,ll,rr,c);
}
inline void update(int pos,int l,int r,const int &oll,const int &orr,const int &ill,const int &irr,const int &c) {
    if( oll <= l && r <= orr ) return update(root[pos],1,n,ill,irr,c);
    const int mid = ( l + r ) >> 1;
    if( orr <= mid ) update(olson[pos],l,mid,oll,orr,ill,irr,c);
    else if( oll > mid ) update(orson[pos],mid+1,r,oll,orr,ill,irr,c);
    else update(olson[pos],l,mid,oll,orr,ill,irr,c) , update(orson[pos],mid+1,r,oll,orr,ill,irr,c);
}
inline void query(int pos,int l,int r,const int &tar) {
    if( !pos ) return;
    ans = merge(ans,f[pos]);
    if( l == r ) return;
    const int mid = ( l + r ) >> 1;
    if( tar <= mid ) query(lson[pos],l,mid,tar);
    else query(rson[pos],mid+1,r,tar);
}
inline void query(int pos,int l,int r,const int &otar,const int &itar) {
    query(root[pos],1,n,itar);
    if( l == r ) return;
    const int mid = ( l + r ) >> 1;
    if( otar <= mid ) query(olson[pos],l,mid,otar,itar);
    else query(orson[pos],mid+1,r,otar,itar);
}
inline void modify(int l,int r) {
    const lli p = fastpow(r-l+1,mod-2);
    if( l != 1 ) {
        update(1,1,n,1,l-1,l,r,(1-p+mod)%mod);
        update(root[0],1,n,1,l-1,0);
    }
    if( r != n ) {
        update(1,1,n,l,r,r+1,n,(1-p+mod)%mod);
        update(root[0],1,n,r+1,n,0);
    }
    if( l != r ) update(1,1,n,l,r,l,r,(1-p*2%mod+mod)%mod);
    update(root[0],1,n,l,r,p);
}
inline void getans(int l,int r) {
    ans = 1;
    if( l == 1 ) return query(root[0],1,n,r);
    else query(1,1,n,l-1,r);
}

int main() {
    static int m;
    scanf("%d%d",&n,&m) , build(1,1,n);
    for(int i=1,o,l,r;i<=m;i++) {
        scanf("%d%d%d",&o,&l,&r);
        if( o == 1 ) modify(l,r);
        else if( o == 2 ) {
            getans(l,r);
            printf("%lld\n",ans);
        }
    }
    return 0;
}
