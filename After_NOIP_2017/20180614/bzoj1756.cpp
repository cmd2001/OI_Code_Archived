#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=getchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret * fix;
}

struct SegmentTree {
    struct Node {
        int ml,mr,mx,su;
        friend Node operator + (const Node &l,const Node &r) {
            return (Node){max(l.ml,l.su+r.ml),max(r.mr,r.su+l.mr),max(l.mr+r.ml,max(l.mx,r.mx)),l.su+r.su};
        }
        inline void fill(int t) {
            ml = mr = mx = su = t;
        }
    }dat[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        if( l == r ) return dat[pos].fill(getint());
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
        dat[pos] = dat[lson(pos)] + dat[rson(pos)];
    }
    inline void update(int pos,int l,int r,const int &tar) {
        if( l == r ) return dat[pos].fill(getint());
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar) : update(rson(pos),mid+1,r,tar);
        dat[pos] = dat[lson(pos)] + dat[rson(pos)];
    }
    inline Node query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        else return query(lson(pos),l,mid,ll,rr) + query(rson(pos),mid+1,r,ll,rr);
    }
}sgt;

int main() {
    static int n,m;
    n = getint() , m = getint() , sgt.build(1,1,n);
    for(int i=1,l,r;i<=m;i++) {
        if( getint() == 1 ) l = getint() , r = getint() , printf("%d\n",sgt.query(1,1,n,min(l,r),max(l,r)).mx);
        else sgt.update(1,1,n,getint());
    }
    return 0;
}
