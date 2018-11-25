#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const int mod=1e9+7;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

bool reseted[maxn<<2];
struct SegmentTree {
    int su[maxn<<2],lazy[maxn<<2],dat[maxn<<2],siz[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void apply(const int &pos,const int &x) {
        adde(su[pos],mul(siz[pos],x)) , adde(lazy[pos],x) , adde(dat[pos],x);
    }
    inline void push(const int &pos) {
        if( lazy[pos] ) apply(lson(pos),lazy[pos]) , apply(rson(pos),lazy[pos]) , lazy[pos] = 0;
    }
    inline void maintain(int pos) {
        su[pos] = su[lson(pos)] + su[rson(pos)] , siz[pos] = siz[lson(pos)] + siz[rson(pos)];
    }
    inline void build(int pos,int l,int r) {
        su[pos] = lazy[pos] = dat[pos] = siz[pos] = 0 , reseted[pos] = 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
    }
    inline void update_val(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if( ll <= l && r <= rr ) return apply(pos,x);
        const int mid = ( l + r ) >> 1; push(pos);
        if( ll <= mid ) update_val(lson(pos),l,mid,ll,rr,x);
        if( mid < rr ) update_val(rson(pos),mid+1,r,ll,rr,x);
        maintain(pos);
    }
    inline void update_siz(int pos,int l,int r,const int &tar) {
        if( l == r ) return adde(siz[pos],1) , adde(su[pos],dat[pos]);
        const int mid = ( l + r ) >> 1; push(pos);
        tar <= mid ? update_siz(lson(pos),l,mid,tar) : update_siz(rson(pos),mid+1,r,tar);
        maintain(pos);
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return su[pos];
        const int mid = ( l + r ) >> 1; push(pos);
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return add(query(lson(pos),l,mid,ll,rr),query(rson(pos),mid+1,r,ll,rr));
    }
}sgt;

int xsrt[maxn],xlen;
int sl[maxn],sr[maxn],n,ans;
struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.y < b.y;
    }
}ps[maxn];


int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&ps[i].x,&ps[i].y) , xsrt[i] = ps[i].x;
    sort(ps+1,ps+1+n) , sort(xsrt+1,xsrt+1+n) , xlen = unique(xsrt+1,xsrt+1+n) - xsrt - 1;
    for(int i=1;i<=n;i++) ps[i].x = lower_bound(xsrt+1,xsrt+1+xlen,ps[i].x) - xsrt;

    // calc sl .
    sgt.build(1,1,xlen);
    for(int i=1;i<=n;i++) if( ps[i].x != xlen ) sgt.update_val(1,1,xlen,ps[i].x+1,xlen,1);
    for(int l=1,r;l<=n;l=r+1) {
        for(r=l;r<n&&ps[r+1].y==ps[l].y;r++) ;
        for(int i=l;i<=r;i++) if( ps[i].x != xlen ) sgt.update_val(1,1,xlen,ps[i].x+1,xlen,mod-1);
        for(int i=l;i<=r;i++) if( ps[i].x != 1 ) sl[i] = sgt.query(1,1,xlen,1,ps[i].x-1);
        for(int i=l;i<=r;i++) sgt.update_siz(1,1,xlen,ps[i].x);
    }

    //calc sr .
    sgt.build(1,1,xlen);
    for(int i=1;i<=n;i++) if( ps[i].x != 1 ) sgt.update_val(1,1,xlen,1,ps[i].x-1,1);
    for(int l=1,r;l<=n;l=r+1) {
        for(r=l;r<n&&ps[r+1].y==ps[l].y;r++) ;
        for(int i=l;i<=r;i++) if( ps[i].x != 1 ) sgt.update_val(1,1,xlen,1,ps[i].x-1,mod-1);
        for(int i=l;i<=r;i++) if( ps[i].x != xlen ) sr[i] = sgt.query(1,1,xlen,ps[i].x+1,xlen);
        for(int i=l;i<=r;i++) sgt.update_siz(1,1,xlen,ps[i].x);
    }

    for(int i=1;i<=n;i++) adde(ans,mul(sl[i],sr[i]));
    printf("%d\n",ans);

    return 0;
}