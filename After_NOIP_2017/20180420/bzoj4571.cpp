#include<cstdio>
const int maxn=2e5+1e2,maxe=2e7+1e2,lim=3e5;

struct PersistentSegmenrTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int& pos,int pre,int l,int r,const int &tar) {
        pos = ++cnt , sum[pos] = sum[pre] + 1;
        if( l == r )  return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];
    }
    inline int query(int pos,int pre,int l,int r,const int &ll,const int &rr) {
        if( sum[pos] == sum[pre] || rr < l || r < ll ) return 0;
        if( ll <= l && r <= rr ) return sum[pos] - sum[pre];
        const int mid = ( l + r ) >> 1;
        return query(lson[pos],lson[pre],l,mid,ll,rr) + query(rson[pos],rson[pre],mid+1,r,ll,rr);
    }
}pst;

int root[maxn];

inline int query(int b,int delta,int root,int pre) {
    int now = 0 , l , r;
    for(int bit=19;~bit;bit--) {
        if( ( b & ( 1 << bit) ) ) { // we need 0 .
            l = now - delta , r = l + ( 1 << bit ) - 1;
            if( ! pst.query(root,pre,1,lim,l,r) ) now |= ( 1 << bit );
        } else {
            l = now + ( 1 << bit ) - delta , r = l + ( 1 << bit ) - 1;
            if( pst.query(root,pre,1,lim,l,r) ) now |= ( 1 << bit );
        }
    }
    return now ^ b;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , pst.insert(root[i],root[i-1],1,lim,t);
    for(int i=1,b,d,l,r;i<=m;i++) scanf("%d%d%d%d",&b,&d,&l,&r) , printf("%d\n",query(b,d,root[r],root[l-1]));
    return 0;
}