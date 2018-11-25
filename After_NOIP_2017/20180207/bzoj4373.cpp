#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=3e5+1e2;
typedef pair<int,int> pi;

int in[maxn];
struct SegmentTree1 {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],mi[maxn<<3],mx[maxn<<3],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) {
            mi[pos] = mx[pos] = in[ll];
            return;
        }
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        mi[pos] = min( mi[lson[pos]] , mi[rson[pos]] ) ,
        mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] ) ;
    }
    inline void update(int pos,int tar,int x) {
        if( tar < l[pos] || r[pos] < tar ) return;
        if( l[pos] == r[pos] ) {
            mi[pos] = mx[pos] = x;
            return;
        }
        update(lson[pos],tar,x) , update(rson[pos],tar,x);
        mi[pos] = min( mi[lson[pos]] , mi[rson[pos]] ) ,
        mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] ) ;
        
    }
    inline pi query(int pos,int ll,int rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return make_pair(mi[pos],mx[pos]);
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return query(lson[pos],ll,rr);
        if( ll > mid ) return query(rson[pos],ll,rr);
        pi ql = query(lson[pos],ll,rr) , qr = query(rson[pos],ll,rr);
        return make_pair(min(ql.first,qr.first),max(ql.second,qr.second));
    }
}sum;

struct SegmentTree2 {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],dat[maxn<<3],cnt;
    inline int gcd(int x,int y) {
        if( !~x || !~y || !x || !y ) return -1;
        register int t;
        while( t = x % y )
            x = y , y = t;
        return y;
    }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) {
            dat[pos] = abs( in[ll] - in[ll+1] );
            return;
        }
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        dat[pos] = gcd( dat[lson[pos]] , dat[rson[pos]] );
    }
    inline void update(int pos,int tar) {
        if( tar < l[pos] || r[pos] < tar ) return;
        if( l[pos] == r[pos] ) {
            dat[pos] = abs( in[tar] - in[tar+1] );
            return;
        }
        update(lson[pos],tar) , update(rson[pos],tar);
        dat[pos] = gcd( dat[lson[pos]] , dat[rson[pos]] );
    }
    inline int query(int pos,int ll,int rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return dat[pos];
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return query(lson[pos],ll,rr);
        if( ll > mid ) return query(rson[pos],ll,rr);
        return gcd( query(lson[pos],ll,rr) , query(rson[pos],ll,rr) );
    }
}gcd;

int main() {
    static int n,m,cnt=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    sum.build(sum.cnt=1,1,n);
    if( n != 1 ) gcd.build(gcd.cnt=1,1,n-1);
    for(int i=1,o,x,y,l,r,k;i<=m;i++) {
        scanf("%d",&o);
        if( o == 2 ) {
            scanf("%d%d%d",&l,&r,&k) , l^= cnt , r ^= cnt , k ^= cnt;
            if( l == r ) {
                puts("Yes") , ++cnt;
                continue;
            }
            pi t = sum.query(1,l,r);
            if( t.second == t.first + ( r - l ) * k ) {
                if( !k ) {
                    puts("Yes") , ++cnt;
                } else {
                    int g = gcd.query(1,l,r-1);
                    if( ~g && ! ( g % k ) ) puts("Yes") , ++cnt;
                    else puts("No");
                }
            } else {
                puts("No");
            }
        } else {
            scanf("%d%d",&x,&y) , x ^= cnt , y ^= cnt;
            in[x] = y;
            sum.update(1,x,y);
            if( x != 1 ) gcd.update(1,x-1);
            if( x != n ) gcd.update(1,x);
        }
    }
    return 0;
}
