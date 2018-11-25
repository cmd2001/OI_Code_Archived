#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

struct SegmentTree {
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],sum[maxn<<2],mx[maxn<<2],cnt;
    SegmentTree() { cnt = 1; }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void update_sum(int pos,const int &tar,const int &x) {
        if( l[pos] == r[pos] ) return void(sum[pos]=x);
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) update_sum(lson[pos],tar,x);
        else update_sum(rson[pos],tar,x);
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline void update_mx(int pos,const int &tar,const int &x) {
        if( l[pos] == r[pos] ) return void(mx[pos]=x);
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) update_mx(lson[pos],tar,x);
        else update_mx(rson[pos],tar,x);
        mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] );
    }
    inline int query_sum(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return 0;
        if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
        return query_sum(lson[pos],ll,rr) + query_sum(rson[pos],ll,rr);
    }
    inline int query_mx(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return -1;
        if( ll <= l[pos] && r[pos] <= rr ) return mx[pos];
        return max( query_mx(lson[pos],ll,rr) , query_mx(rson[pos],ll,rr) );
    }
}sgt;

int inx[maxn],iny[maxn],n;

inline int dis(int t) { // return dis from in[t] to in[t+1] .
    return abs(inx[t]-inx[t+1]) + abs(iny[t]-iny[t+1]);
}
inline int crs(int t) {
    return abs(inx[t-1]-inx[t+1]) + abs(iny[t-1]-iny[t+1]);
}
inline void update(int t) {
    if( t != 1 ) {
        int dd = dis(t-1);
        sgt.update_sum(1,t-1,dd);
        if( t != 2 ) {
            int delta = dis(t-2) + dis(t-1) - crs(t-1);
            sgt.update_mx(1,t-1,delta);
        }
    }
    if( t != n ) {
        int dd = dis(t) , delta = dis(t-1) + dis(t) - crs(t);
        sgt.update_sum(1,t,dd) , sgt.update_mx(1,t,delta);
        if( t != n - 1 ) {
            delta = dis(t) + dis(t+1) - crs(t+1);
            sgt.update_mx(1,t+1,delta);
        }
    }
}

int main() {
    static int m;
    static char o[10];
    scanf("%d%d",&n,&m) , sgt.build(1,1,n);
    for(int i=1;i<=n;i++) scanf("%d%d",inx+i,iny+i);
    for(int i=1;i<n;i++) sgt.update_sum(1,i,dis(i));
    for(int i=2;i<n;i++) sgt.update_mx(1,i,dis(i-1)+dis(i)-crs(i));
    for(int i=1,t,l,r,ans;i<=m;i++) {
        scanf("%s",o);
        if( *o == 'Q' ) {
            scanf("%d%d",&l,&r);
            if( l == r ) puts("0");
            else {
                ans = sgt.query_sum(1,l,r-1);
                if( l != r + 1 ) ans -= max( 0 , sgt.query_mx(1,l+1,r-1) );
                printf("%d\n",ans);
            }
        } else if( *o == 'U' ) {
            scanf("%d",&t) , scanf("%d%d",inx+t,iny+t) , update(t);
        }
    }
    return 0;
}
