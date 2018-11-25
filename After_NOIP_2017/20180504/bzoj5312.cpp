#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<cctype>
const unsigned maxn=2e5+1e2,maxe=(maxn<<2)+5;
const unsigned full = ( 1 << 21 ) - 1;

unsigned in[maxn];
struct SegmentTree {
    unsigned andsu[maxe],orsu[maxe],lazyand[maxe],lazyor[maxe],mx[maxe];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void upgrade(unsigned pos) {
        andsu[pos] = andsu[lson(pos)] & andsu[rson(pos)] , orsu[pos] = orsu[lson(pos)] | orsu[rson(pos)] , mx[pos] = std::max( mx[lson(pos)] , mx[rson(pos)] );
    }
    inline void build(unsigned pos,unsigned ll,unsigned rr) {
        lazyand[pos] = full;
        if( ll == rr ) return void( andsu[pos] = orsu[pos] = mx[pos] = in[ll] );
        const unsigned mid = ( ll + rr ) >> 1;
        build(lson(pos),ll,mid) , build(rson(pos),mid+1,rr) , upgrade(pos);
    }
    inline void apply(unsigned pos,const unsigned &x,const unsigned &tpe) { // tpe = 1 means and , tpe = 2 means or .
        if( tpe == 1 ) andsu[pos] &= x , orsu[pos] &= x , lazyand[pos] &= x , lazyor[pos] &= x , mx[pos] &= x;
        else if( tpe == 2 ) andsu[pos] |= x , orsu[pos] |= x , lazyor[pos] |= x , mx[pos] |= x;
    }
    inline void push(unsigned pos) {
        if( lazyand[pos] != full ) apply(lson(pos),lazyand[pos],1) , apply(rson(pos),lazyand[pos],1) , lazyand[pos] = full;
        if( lazyor ) apply(lson(pos),lazyor[pos],2) , apply(rson(pos),lazyor[pos],2) , lazyor[pos] = 0;
    }
    inline bool allsame(unsigned pos,const unsigned &x,const unsigned &tpe) {
        unsigned dif = andsu[pos] ^ orsu[pos] , ref = ( tpe == 1 ? 0 : full ) ^ x;
        return ! ( dif & ref );
    }
    inline void update(unsigned pos,unsigned l,unsigned r,const unsigned &ll,const unsigned &rr,const unsigned &x,const unsigned &tpe) {
        if( ll <= l && r <= rr && allsame(pos,x,tpe) ) return apply(pos,x,tpe);
        push(pos); const unsigned mid = ( l + r ) >> 1;
        if( rr <= mid ) update(lson(pos),l,mid,ll,rr,x,tpe);
        else if( ll > mid ) update(rson(pos),mid+1,r,ll,rr,x,tpe);
        else update(lson(pos),l,mid,ll,rr,x,tpe) , update(rson(pos),mid+1,r,ll,rr,x,tpe);
        upgrade(pos);
    }
    inline unsigned query(unsigned pos,unsigned l,unsigned r,const unsigned &ll,const unsigned &rr) {
        if( ll <= l && r <= rr ) return mx[pos];
        push(pos); const unsigned mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return std::max( query(lson(pos),l,mid,ll,rr) , query(rson(pos),mid+1,r,ll,rr) );
    }
}sgt;

inline char nextchar() {
    static const unsigned BS = 1 << 22;
    static unsigned char buf[BS],*st=buf+BS,*ed=st;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline unsigned getint() {
    unsigned ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static unsigned n,m;
    n = getint() , m = getint(); for(unsigned i=1;i<=n;in[i++]=getint());
    sgt.build(1,1,n);
    for(unsigned i=1,o,l,r,x;i<=m;i++) o = getint() , l = getint() , r = getint() , o == 3 ? printf("%d\n",sgt.query(1,1,n,l,r)) : x = getint() , sgt.update(1,1,n,l,r,x,o);
    return 0;
}

