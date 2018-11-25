#include<cstdio>
#include<cctype>
typedef unsigned int uint;
typedef unsigned long long int ulli;
typedef unsigned char uchar;
const int maxn=1e5+1e2;

uint mod;
inline uint add(const uint &x,const uint &y) {
    const uint ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline uint mul(const uint &x,const uint &y) {
    return (ulli) x * y % mod;
}
inline uint fix(uint x) {
    while( x >= mod ) x -= mod;
    while( x < 0 ) x += mod;
    return x;
}
inline void adde(uint &dst,const uint &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void mule(uint &dst,const uint &x) {
    dst = (ulli) dst * x % mod;
}

enum Operate{MUL,ADD};
const uint iniv[]={1u,0u};

uint in[maxn],n;

struct SegmentTree {
    uint su[maxn<<2],lazy[maxn<<2][2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void apply(uint pos,const uint &l,const uint &r,const Operate &ope,const uint &x) {
        if( !ope ) mule(su[pos],x) , mule(lazy[pos][0],x) , mule(lazy[pos][1],x);
        else adde(su[pos],mul(x,r-l+1)) , adde(lazy[pos][1],x);
    }
    inline void push(const uint &pos,const uint &l,const uint &mid,const uint &r) {
        for(int i=0;i<2;i++) if( lazy[pos][i] != iniv[i] ) {
            apply(lson(pos),l,mid,(Operate)i,lazy[pos][i]) , apply(rson(pos),mid+1,r,(Operate)i,lazy[pos][i]);
            lazy[pos][i] = iniv[i];
        } 
    }
    inline void maintain(uint pos) {
        su[pos] = add(su[lson(pos)],su[rson(pos)]);
    }
    inline void build(uint pos,uint l,uint r) {
        for(int i=0;i<2;i++) lazy[pos][i] = iniv[i];
        if( l == r ) return void( su[pos] = fix(in[l]) );
        const uint mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , maintain(pos);
    }
    inline void update(uint pos,uint l,uint r,const uint &ll,const uint &rr,const Operate ope,const uint &x) {
        if( ll <= l && r <= rr ) return apply(pos,l,r,ope,x);
        const uint mid = ( l + r ) >> 1; push(pos,l,mid,r);
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr,ope,x);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,ope,x);
        maintain(pos);
    }
    inline uint query(uint pos,uint l,uint r,const uint &ll,const uint &rr) {
        if( ll <= l && r <= rr ) return su[pos];
        const uint mid = ( l + r ) >> 1; push(pos,l,mid,r);
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return add(query(lson(pos),l,mid,ll,rr),query(rson(pos),mid+1,r,ll,rr));
    }
}sgt;

namespace IO {
    inline uchar nextchar() {
        static const uint BS = 1 << 21;
        static uchar buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? 0 : *st++;
    }
    inline uint getint() {
        uint ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using IO::getint;

int main() {
    n = getint() , mod = getint();
    for(uint i=1;i<=n;i++) in[i] = getint();
    sgt.build(1,1,n);
    for(uint i=1,m=getint(),o,l,r;i<=m;i++) {
        o = getint() , l = getint() , r = getint();
        if( o <= 2 ) sgt.update(1,1,n,l,r,(Operate)(o-1),getint());
        else printf("%u\n",sgt.query(1,1,n,l,r));
    }
    return 0;
}

