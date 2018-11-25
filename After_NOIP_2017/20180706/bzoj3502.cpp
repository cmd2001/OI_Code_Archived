#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=2097155;
 
int in[maxn>>1],n;
struct SegmentTree {
    bool lazy[maxn];
    struct Node {
        lli mxl,mxr,mx,sum;
        int l,r,mxl_pos,mxr_pos,mx_pos_l,mx_pos_r;
        __inline friend Node operator + (const Node &a,const Node &b) {
            Node ret = (Node){a.mxl,b.mxr,a.mx,a.sum+b.sum,a.l,b.r,a.mxl_pos,b.mxr_pos,a.mx_pos_l,a.mx_pos_r};
            if( b.mx > a.mx ) ret.mx = b.mx , ret.mx_pos_l = b.mx_pos_l , ret.mx_pos_r = b.mx_pos_r;
            if( a.mxr + b.mxl > ret.mx ) ret.mx = a.mxr + b.mxl , ret.mx_pos_l = a.mxr_pos , ret.mx_pos_r = b.mxl_pos; // assert mxr >= sum && mxl >= sum .
            if( ret.mxl < a.sum + b.mxl ) ret.mxl = a.sum + b.mxl , ret.mxl_pos = b.mxl_pos;
            if( ret.mxr < a.mxr + b.sum ) ret.mxr = a.mxr + b.sum , ret.mxr_pos = a.mxr_pos;
            return ret;
        }
        __inline void fill(int pos,int in) {
            mxl = mxr = mx = sum = in , l = r = mxl_pos = mxr_pos = mx_pos_l = mx_pos_r = pos;
        }
    }org[maxn],neg[maxn];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int ll,int rr) {
        if( ll == rr ) return org[pos].fill(ll,in[ll]) , neg[pos].fill(ll,-in[ll]);
        const int mid = ( ll + rr ) >> 1;
        build(lson(pos),ll,mid) , build(rson(pos),mid+1,rr);
        org[pos] = org[lson(pos)] + org[rson(pos)] , neg[pos] = neg[lson(pos)] + neg[rson(pos)];
    }
    __inline void apply(int pos) {
        lazy[pos] ^= 1 , std::swap(org[pos],neg[pos]);
    }
    __inline void push(int pos) {
        if( lazy[pos] ) apply(lson(pos)) , apply(rson(pos)) , lazy[pos] = 0;
    }
    __inline Node query() {
        return org[1];
    }
    inline void update_neg(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return apply(pos);
        push(pos); const int mid = ( l + r ) >> 1;
        if( rr <= mid ) update_neg(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) update_neg(rson(pos),mid+1,r,ll,rr);
        else update_neg(lson(pos),l,mid,ll,rr) , update_neg(rson(pos),mid+1,r,ll,rr);
        org[pos] = org[lson(pos)] + org[rson(pos)] , neg[pos] = neg[lson(pos)] + neg[rson(pos)];
    }
}sgt;
typedef SegmentTree::Node Node;
 
inline lli solve_case(int k) {
    lli ret = 0;
    while(k--) {
        Node now = sgt.query();
        if( now.mx <= 0 ) break;
        ret += now.mx , sgt.update_neg(1,1,n,now.mx_pos_l,now.mx_pos_r);
    }
    return ret;
}

inline char nextchar() {
    static const int BS = 1 << 22;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , fix = 1; char ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}

 
int main() {
    static int m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    sgt.build(1,1,n) , printf("%lld\n",solve_case(m));
    return 0;
}

