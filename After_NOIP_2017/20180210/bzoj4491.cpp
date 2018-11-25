#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

struct Node {
    int sl,sr,smid,len;
    friend Node operator + (const Node &l,const Node &r) {
        Node ret = (Node){l.sl,r.sr,max(max(l.smid,r.smid),l.sr+r.sl),l.len+r.len};
        if( l.smid == l.len ) ret.sl = l.len + r.sl;
        if( r.smid == r.len ) ret.sr = l.sr + r.len;
        ret.smid = max( ret.smid , max( ret.sl , ret.sr ) );
        return ret;
    }
}abo[maxn<<2],bel[maxn<<2];

int in[maxn];
int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],cnt;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        abo[pos] = (Node){in[ll]>=0,in[ll]>=0,in[ll]>=0,1};
        bel[pos] = (Node){in[ll]<=0,in[ll]<=0,in[ll]<=0,1};
        return;
    } const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    abo[pos] = abo[lson[pos]] + abo[rson[pos]] ,
    bel[pos] = bel[lson[pos]] + bel[rson[pos]] ;
}
inline Node queryabo(int pos,int ll,int rr) {
    if( ll <= l[pos] && r[pos] <= rr ) return abo[pos];
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid ) return queryabo(lson[pos],ll,rr);
    if( ll > mid ) return queryabo(rson[pos],ll,rr);
    return queryabo(lson[pos],ll,rr) + queryabo(rson[pos],ll,rr);
}
inline Node querybel(int pos,int ll,int rr) {
    if( ll <= l[pos] && r[pos] <= rr ) return bel[pos];
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid ) return querybel(lson[pos],ll,rr);
    if( ll > mid ) return querybel(rson[pos],ll,rr);
    return querybel(lson[pos],ll,rr) + querybel(rson[pos],ll,rr);
}

int main() {
    static int n,q;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<n;i++) in[i] = in[i+1] - in[i];
    if( n != 1 ) build(cnt=1,1,n-1);
    scanf("%d",&q);
    for(int i=1,l,r,ans;i<=q;i++) {
        scanf("%d%d",&l,&r);
        if( l == r ) {
            puts("1"); continue;
        } --r;
        Node abo = queryabo(1,l,r) , bel = querybel(1,l,r);
        ans = 1 + max( abo.smid , bel.smid );
        printf("%d\n",ans);
    }
    return 0;
}
