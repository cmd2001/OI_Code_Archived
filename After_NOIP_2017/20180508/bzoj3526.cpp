#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=2e5+1e2;

int in[maxn][2];

struct SegmentTree {
    struct Node {
        int f[2],l,r; // first[0/1] .
        friend Node operator + (const Node &a,const Node &b) { // assert f[0] <= f[1] .
            Node ret = (Node){-1,-1,a.l,b.r};
            if( ~a.f[0] ) {
                if( ~b.f[0] && in[a.r][a.f[0]] <= in[b.l][0] ) ret.f[0] = b.f[0];
                else if( ~b.f[1] && in[a.r][a.f[0]] <= in[b.l][1] ) ret.f[0] = b.f[1];
            }
            if( ~a.f[1] ) {
                if( ~b.f[0] && in[a.r][a.f[1]] <= in[b.l][0] ) ret.f[1] = b.f[0];
                else if( ~b.f[1] && in[a.r][a.f[1]] <= in[b.l][1] ) ret.f[1] = b.f[1];
            }
            return ret;
        }
        inline void fil(int pos) {
            f[0] = 0 , f[1] = 1 , l = r = pos;
        }
    }ns[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        if( l == r ) return ns[pos].fil(l);
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , ns[pos] = ns[lson(pos)] + ns[rson(pos)];
    }
    inline void update(int pos,int l,int r,const int &tar) {
        if( l == r ) return ns[pos].fil(l);
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) update(lson(pos),l,mid,tar);
        else update(rson(pos),mid+1,r,tar);
        ns[pos] = ns[lson(pos)] + ns[rson(pos)];
    }
    inline Node query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return ns[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return query(lson(pos),l,mid,ll,rr) + query(rson(pos),mid+1,r,ll,rr);
    }
}sgt;
typedef SegmentTree::Node Node;

inline char nxtchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=st;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nxtchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nxtchar()) );
    return ret;
}
int main() {
    static int n,m;
    n = getint();
    for(int i=1;i<=n;i++) {
        in[i][0] = getint() , in[i][1] = getint();
        if( in[i][0] > in[i][1] ) std::swap(in[i][0],in[i][1]);
    }
    m = getint() , sgt.build(1,1,n);
    for(int i=1,l0,l1,r0,r1,l,r;i<=m;i++) {
        l = getint() , r = getint() , l0 = in[l][0] , l1 = in[l][1] , r0 = in[r][0] , r1 = in[r][1];
        in[l][0] = r0 , in[l][1] = r1 , sgt.update(1,1,n,l);
        in[r][0] = l0 , in[r][1] = l1 , sgt.update(1,1,n,r);
        Node ans = sgt.query(1,1,n,1,n);
        if( ~ans.f[0] || ~ans.f[1] ) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
