#include<cstdio>
#include<algorithm>
typedef unsigned long long int ulli;
const int maxn=1e4+1e2;
const ulli base = 3;

ulli pows[maxn];
struct SegmentTree {
    ulli dat[maxn<<2][2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        if( l == r ) return void( dat[pos][0] = dat[pos][1] = 0 );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
        dat[pos][0] = dat[lson(pos)][0] * pows[r-mid] + dat[rson(pos)][0];
        dat[pos][1] = dat[rson(pos)][1] * pows[mid-l+1] + dat[lson(pos)][1];
    }
    inline void update(int pos,int l,int r,const int &tar) {
        if( l == r ) return void( dat[pos][0] = dat[pos][1] = 1 );
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar) : update(rson(pos),mid+1,r,tar);
        dat[pos][0] = dat[lson(pos)][0] * pows[r-mid] + dat[rson(pos)][0];
        dat[pos][1] = dat[rson(pos)][1] * pows[mid-l+1] + dat[lson(pos)][1];
    }
    inline ulli query(int pos,int l,int r,const int &ll,const int &rr,const int &tpe) {
        if( ll <= l && r <= rr ) return dat[pos][tpe];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr,tpe);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr,tpe);
        const ulli ql = query(lson(pos),l,mid,ll,mid,tpe) , qr = query(rson(pos),mid+1,r,mid+1,rr,tpe);
        if( !tpe ) return ql * pows[rr-mid] + qr;
        else return qr * pows[mid-ll+1] + ql;
    }
}sgt;

static int in[maxn];

int main() {
    static int t,n,ans;
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&n) , sgt.build(1,1,n) , ans = 0;
        *pows = 1; for(int i=1;i<=n;i++) pows[i] = pows[i-1] * base;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        for(int i=1;i<=n;i++) {
            int len = std::min( in[i] - 1 , n - in[i] );
            if( len && sgt.query(1,1,n,in[i]-len,in[i]-1,0) != sgt.query(1,1,n,in[i]+1,in[i]+len,1) ) {
                ans = 1; break;
            }
            sgt.update(1,1,n,in[i]);
        }
        puts(ans?"Y":"N");
    }
    return 0;
}
