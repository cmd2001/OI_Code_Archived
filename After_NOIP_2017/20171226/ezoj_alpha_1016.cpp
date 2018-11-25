#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2;
const int inf=0x3f3f3f3f;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
    lli dat[maxn<<3],sum[maxn<<3],lazy[maxn<<3];
    int cnt; // data means max val.
    
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll ,r[pos] = rr;
        if( ll == rr)
            return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void push(int pos) {
        if( lazy[pos] ) {
            if( lson[pos] ) {
                dat[lson[pos]] = lazy[lson[pos]] = lazy[pos],
                sum[lson[pos]] = lazy[pos] * ( r[lson[pos]] - l[lson[pos]] + 1 );
            }
            if( rson[pos] ) {
                dat[rson[pos]] = lazy[rson[pos]] = lazy[pos],
                sum[rson[pos]] = lazy[pos] * ( r[rson[pos]] - l[rson[pos]] + 1 );
            }
            lazy[pos] = 0;
        }
    }
    inline void update(int pos,int ll,int rr,lli x) {
        if( rr < l[pos] || r[pos] < ll )
            return;
        if( ll <= l[pos] && r[pos] <= rr ) {
            dat[pos] = lazy[pos] = x;
            sum[pos] = x * ( r[pos] - l[pos] + 1 );
            return;
        }
        push(pos);
        update(lson[pos],ll,rr,x);
        update(rson[pos],ll,rr,x);
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
        dat[pos] = max( dat[lson[pos]] , dat[rson[pos]] );
    }
    inline int upper(int pos,int tar) { // find the latest pos whose dat >= tar.
        if( l[pos] == r[pos] ) {
            if( dat[pos] < tar )
                debug<<"There must be an error!"<<endl;
            return l[pos];
        }
        push(pos);
        if( dat[rson[pos]] >= tar )
            return upper(rson[pos],tar);
        return upper(lson[pos],tar);
    }
    inline lli query(int pos,int ll,int rr) {
        if( rr < l[pos] || r[pos] < ll )
            return 0;
        if( ll <= l[pos] && r[pos] <= rr )
            return sum[pos];
        push(pos);
        return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
}segt;

struct Node {
    lli zz;
    int xx,yy;
    friend bool operator < (const Node &a,const Node &b) {
        return a.zz < b.zz;
    }
}ns[maxn];

int mxx[maxn],mxy[maxn];
int zz,xx,yy;
int n,m;
lli ans;

inline void init() {
    ns[++n] = (Node){zz,0,0};
    sort(ns+1,ns+1+n);
    for(int i=n;i;i--)
        mxx[i] = max( mxx[i+1] , ns[i].xx ),
        mxy[i] = max( mxy[i+1] , ns[i].yy );
    segt.build(segt.cnt=1,0,xx);
    segt.update(1,0,0,inf);
}

inline void getans() {
    int last = 0;
    for(int i=1;i<=n;i++) {
        int uper = segt.upper(1,ns[i].yy);
        if( uper < ns[i].xx )
            segt.update(1,uper+1,ns[i].xx,ns[i].yy);
        if( ns[i].zz == ns[i+1].zz )
            continue;
        const lli len = ns[i].zz - last;
        last = ns[i].zz;
        lli full = ( xx - mxx[i+1] ) * yy;
        uper = segt.upper(1,mxy[i+1]);
        lli minus = segt.query(1,mxx[i+1]+1,uper) + 1LL * ( xx - uper ) * mxy[i+1];
        ans += len * ( full - minus );
    }
}


int main() {
    scanf("%d%d%d%d",&n,&zz,&xx,&yy);
    for(int i=1;i<=n;i++)
        scanf("%lld%d%d",&ns[i].zz,&ns[i].xx,&ns[i].yy);
    
    init();
    getans();
    
    printf("%lld\n",ans);
    
    return 0;
}