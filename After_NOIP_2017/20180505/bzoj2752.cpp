#include<cstdio>
typedef long long int lli;
const int maxn=1e5+1e2;

struct SegmentTree {
    struct Node {
        lli l,mi,mii;
        friend Node operator + (const Node &a,const Node &b) {
            return (Node){a.l+b.l,a.mi+b.mi,a.mii+b.mii};
        }
        inline void in(const lli &v,lli s,lli si,lli sii) {
            l += v * s , mi += v * si, mii += v * sii;
        }
    }ns[maxn<<2];
    lli s[maxn<<2],si[maxn<<2],sii[maxn<<2],lazy[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        if( l == r ) {
            s[pos] = 1 , si[pos] = l , sii[pos] =  (lli) l * l;
            return;
        } const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
        s[pos] = s[lson(pos)] + s[rson(pos)] , si[pos] = si[lson(pos)] + si[rson(pos)] , sii[pos] = sii[lson(pos)] + sii[rson(pos)];
    }
    inline void apply(int pos,const lli &v) {
        lazy[pos] += v , ns[pos].in(v,s[pos],si[pos],sii[pos]);
    }
    inline void push(int pos) {
        if( lazy[pos] ) apply(lson(pos),lazy[pos]) , apply(rson(pos),lazy[pos]) , lazy[pos] = 0;
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const lli &v) {
        if( ll <= l && r <= rr ) return apply(pos,v);
        push(pos); const int mid = ( l + r ) >> 1;
        if( rr <= mid ) update(lson(pos),l,mid,ll,rr,v);
        else if( ll > mid ) update(rson(pos),mid+1,r,ll,rr,v);
        else update(lson(pos),l,mid,ll,rr,v) , update(rson(pos),mid+1,r,ll,rr,v);
        ns[pos] = ns[lson(pos)] + ns[rson(pos)];
    }
    inline Node query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return ns[pos];
        push(pos); const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        else return query(lson(pos),l,mid,ll,rr) + query(rson(pos),mid+1,r,ll,rr);
    }
}sgt;
typedef SegmentTree::Node Node;

inline lli gcd(lli x,lli y) {
    register lli t;
    while( ( t = x % y ) ) x = y , y = t;
    return y;
}
inline lli c(lli x) {
    return x * ( x + 1 ) >> 1;
}

int main() {
    static int n,m;
    static char o[10];
    scanf("%d%d",&n,&m) , sgt.build(1,1,n-1);
    for(int i=1,l,r,x;i<=m;i++) {
        scanf("%s%d%d",o,&l,&r);
        if( *o == 'C' ) scanf("%d",&x) , sgt.update(1,1,n-1,l,r-1,x);
        else if( *o == 'Q' ){
            Node nd = sgt.query(1,1,n-1,l,r-1);
            lli u = ( r + l - 1 ) * nd.mi + r * nd.l - nd.mii - (lli) l * r * nd.l,v = c(r-l);
            lli g = gcd(u,v); u /= g , v /= g;
            printf("%lld/%lld\n",u,v);
        }
    }
    return 0;
}