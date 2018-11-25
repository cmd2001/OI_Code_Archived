#include<cstdio>
#include<cstring>
const int maxn=1e2+1e1,maxe=1e5+1e2;

int u[maxe],v[maxe],c[maxe];
int n;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        return x = findfa(x) , y = findfa(y) , x == y ? 0 : fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

struct SegmentTree {
    int l[maxe<<2],r[maxe<<2],lson[maxe<<2],rson[maxe<<2],cnt;
    SegmentTree() { cnt = 1; }
    struct Node {
        int dat[maxn],len,sum;
        Node() { memset(dat,0,sizeof(dat)) , sum = len = 0; }
        friend Node operator + (const Node &a,const Node &b) {
            Node ret; ufs.init();
            int l = 1 , r = 1 , sel;
            while( l <= a.len || r <= b.len ) {
                if( r > b.len || ( l <= a.len && c[a.dat[l]] < c[b.dat[r]] ) ) sel = a.dat[l++];
                else sel = b.dat[r++];
                if( ufs.merge(u[sel],v[sel]) ) ret.dat[++ret.len] = sel , ret.sum += c[sel];
            }
            return ret;
        }
        inline void fill(const int &id) {
            sum = c[dat[len=1]=id];
        }
    }ns[maxe<<2];
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return ns[pos].fill(ll);
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr) ,
        ns[pos] = ns[lson[pos]] + ns[rson[pos]];
    }
    inline Node query(int pos,const int &ll,const int &rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return ns[pos];
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return query(lson[pos],ll,rr);
        else if( ll > mid ) return query(rson[pos],ll,rr);
        else return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
}sgt;

int main() {
    static int m,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++) scanf("%d%d%d",u+i,v+i,c+i);
    sgt.build(1,1,m);
    for(int i=1,l,r;i<=q;i++) scanf("%d%d",&l,&r) , printf("%d\n",sgt.query(1,l,r).sum);
    return 0;
}
