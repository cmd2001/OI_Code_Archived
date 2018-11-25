#include<cstdio>
#include<algorithm>
const int maxn=1e5+1e2,maxk=25;

int in[maxn];
struct SegmentTree {
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],lazy[maxn<<2],cnt;
    SegmentTree() { cnt = 1; }
    struct Node {
        int mxl,mxr,mx,sum,l,r,mxl_pos,mxr_pos,mx_pos_l,mx_pos_r;
        friend Node operator + (const Node &a,const Node &b) {
            Node ret = (Node){a.mxl,b.mxr,a.mx,a.sum+b.sum,a.l,b.r,a.mxl_pos,b.mxr_pos,a.mx_pos_l,a.mx_pos_r};
            if( b.mx > a.mx ) ret.mx = b.mx , ret.mx_pos_l = b.mx_pos_l , ret.mx_pos_r = b.mx_pos_r;
            if( a.mxr + b.mxl > ret.mx ) ret.mx = a.mxr + b.mxl , ret.mx_pos_l = a.mxr_pos , ret.mx_pos_r = b.mxl_pos; // assert mxr >= sum && mxl >= sum .
            if( ret.mxl < a.sum + b.mxl ) ret.mxl = a.sum + b.mxl , ret.mxl_pos = b.mxl_pos;
            if( ret.mxr < a.mxr + b.sum ) ret.mxr = a.mxr + b.sum , ret.mxr_pos = a.mxr_pos;
            return ret;
        }
        inline void fill(int pos,int in) {
            mxl = mxr = mx = sum = in , l = r = mxl_pos = mxr_pos = mx_pos_l = mx_pos_r = pos;
        }
    }org[maxn<<2],neg[maxn<<2];
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return org[pos].fill(ll,in[ll]) , neg[pos].fill(ll,-in[ll]);
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        org[pos] = org[lson[pos]] + org[rson[pos]] , neg[pos] = neg[lson[pos]] + neg[rson[pos]];
    }
    inline void apply(int pos) {
        lazy[pos] ^= 1 , std::swap(org[pos],neg[pos]);
    }
    inline void push(int pos) {
        if( lazy[pos] ) apply(lson[pos]) , apply(rson[pos]) , lazy[pos] = 0;
    }
    inline Node query(int pos,const int &ll,const int &rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return org[pos];
        push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return query(lson[pos],ll,rr);
        else if( ll > mid ) return query(rson[pos],ll,rr);
        return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
    inline void update_val(int pos,const int &tar,const int &x) {
        if( l[pos] == r[pos] ) return org[pos].fill(tar,x) , neg[pos].fill(tar,-x);
        push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) update_val(lson[pos],tar,x);
        else update_val(rson[pos],tar,x);
        org[pos] = org[lson[pos]] + org[rson[pos]] , neg[pos] = neg[lson[pos]] + neg[rson[pos]];
    }
    inline void update_neg(int pos,const int &ll,const int &rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return apply(pos);
        push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) update_neg(lson[pos],ll,rr);
        else if( ll > mid ) update_neg(rson[pos],ll,rr);
        else update_neg(lson[pos],ll,rr) , update_neg(rson[pos],ll,rr);
        org[pos] = org[lson[pos]] + org[rson[pos]] , neg[pos] = neg[lson[pos]] + neg[rson[pos]];
    }
}sgt;
typedef SegmentTree::Node Node;

int stk_l[maxk],stk_r[maxk],top;

inline int solve_case(int l,int r,int k) {
    int ret = 0;
    while(k--) {
        Node now = sgt.query(1,l,r);
        if( now.mx <= 0 ) break;
        ret += now.mx , stk_l[++top] = now.mx_pos_l , stk_r[top] = now.mx_pos_r , sgt.update_neg(1,now.mx_pos_l,now.mx_pos_r);
    }
    while(top) sgt.update_neg(1,stk_l[top],stk_r[top]) , --top;
    return ret;
}

int main() {
    static int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    sgt.build(1,1,n) , scanf("%d",&m);
    for(int i=1,o,l,r,k,p,v;i<=m;i++) {
        scanf("%d",&o);
        if( !o ) scanf("%d%d",&p,&v) , sgt.update_val(1,p,v);
        else if( o == 1 ) scanf("%d%d%d",&l,&r,&k) , printf("%d\n",solve_case(l,r,k));
    }
    return 0;
}

