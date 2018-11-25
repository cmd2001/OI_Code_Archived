#include<cstdio>
const int maxn=5e4+1e2,maxe=1e6+1e2;

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],dat[maxe],cnt;
    inline void insert(int &pos,int pre,int l,int r,const int &tar) {
        dat[pos=++cnt] = dat[pre] + 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];
    }
    inline int query(int pos,int pre,int l,int r,const int &lim) {
        if( dat[pos] - dat[pre] <= lim ) return 0; // No solution .
        if( l == r ) return l;
        const int mid = ( l + r ) >> 1;
        if( dat[lson[pos]] - dat[lson[pre]] > dat[rson[pos]] - dat[rson[pre]] ) return query(lson[pos],lson[pre],l,mid,lim);
        else return query(rson[pos],rson[pre],mid+1,r,lim);
    }
}pst;

int root[maxn];

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , pst.insert(root[i],root[i-1],1,50000,t);
    for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r) , printf("%d\n",pst.query(root[r],root[l-1],1,50000,(r-l+1)>>1));
    return 0;
}
