#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
typedef long long int lli;
const int maxn=5e5+1e2;

int in[maxn],n;

struct SegmentTree {
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],cnt;
    lli lazy_fil[maxn<<2],lazy_day[maxn<<2],mxv[maxn<<2],mxh[maxn<<2],suv[maxn<<2],suh[maxn<<2];
    SegmentTree() { memset(lazy_fil,-1,sizeof(lazy_fil)) , cnt = 1 ; }
    inline void apply_fil(int pos,lli nv) {
        lazy_fil[pos] = mxh[pos] = nv , suh[pos] = nv * ( r[pos] - l[pos] + 1 ) , lazy_day[pos] = 0;
    }
    inline void apply_day(int pos,lli dd) {
        lazy_day[pos] += dd , mxh[pos] += mxv[pos] * dd , suh[pos] += suv[pos] * dd;
    }
    inline void push(int pos) {
        if( ~lazy_fil[pos] ) apply_fil(lson[pos],lazy_fil[pos]) , apply_fil(rson[pos],lazy_fil[pos]) , lazy_fil[pos] = -1;
        if( lazy_day[pos] ) apply_day(lson[pos],lazy_day[pos]) , apply_day(rson[pos],lazy_day[pos]) , lazy_day[pos] = 0;
    }
    inline void upgrade_build(int pos) {
        mxv[pos] = max( mxv[lson[pos]] , mxv[rson[pos]] ) , suv[pos] = suv[lson[pos]] + suv[rson[pos]];
    }
    inline void upgrade(int pos) {
        suh[pos] = suh[lson[pos]] + suh[rson[pos]] , mxh[pos] = max( mxh[lson[pos]] , mxh[rson[pos]] );
    }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return void(mxv[pos]=suv[pos]=in[ll]);
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr) , upgrade_build(pos);
    }
    inline void update_fil(int pos,const int &ll,const int &rr,const lli &nv) {
        if( ll <= l[pos] && r[pos] <= rr ) return apply_fil(pos,nv);
        const int mid = ( l[pos] + r[pos] ) >> 1; push(pos);
        if( ll <= mid ) update_fil(lson[pos],ll,rr,nv);
        if( mid < rr ) update_fil(rson[pos],ll,rr,nv);
        upgrade(pos);
    }
    inline void update_day(int pos,const int &ll,const int &rr,const lli &dd) {
        if( ll <= l[pos] && r[pos] <= rr ) return apply_day(pos,dd);
        const int mid = ( l[pos] + r[pos] ) >> 1; push(pos);
        if( ll <= mid ) update_day(lson[pos],ll,rr,dd);
        if( mid < rr ) update_day(rson[pos],ll,rr,dd);
        upgrade(pos);
    }
    inline int bin(int pos,const lli &lim) { // find most left pos >= d .
        if( l[pos] == r[pos] ) return mxh[pos] >= lim ? l[pos] : n + 1; // n + 1 means not found .
        push(pos);
        if( mxh[lson[pos]] >= lim ) return bin(lson[pos],lim);
        else return bin(rson[pos],lim);
    }
    inline lli query(int pos,const int &ll,const int &rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return suh[pos];
        const int mid = ( l[pos] + r[pos] ) >> 1; push(pos);
        if( rr <= mid ) return query(lson[pos],ll,rr);
        if( ll > mid ) return query(rson[pos],ll,rr);
        return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
}sgt;


inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0;
    char ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}
inline lli getlli() {
    lli ret = 0;
    char ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int m;
    static lli t,lst,lim;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    std::sort(in+1,in+1+n) , sgt.build(1,1,n);
    for(int i=1,pos;i<=m;i++) {
        t = getlli() , lim = getlli() , sgt.update_day(1,1,n,t-lst) , lst = t;
        pos = sgt.bin(1,lim);
        if( pos <= n ) printf("%lld\n",sgt.query(1,pos,n)-(n-pos+1)*lim) , sgt.update_fil(1,pos,n,lim);
        else puts("0");
    }
    return 0;
}
