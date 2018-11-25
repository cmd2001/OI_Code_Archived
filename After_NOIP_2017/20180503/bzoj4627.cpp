#include<cstdio>
typedef long long int lli;
const int maxn=1e5+1e2,maxe=1e7+1e2;
const lli lim = 1e18;

struct SegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int &pos,lli l,lli r,const lli &tar) {
        if( !pos ) pos = ++cnt;
        ++sum[pos];
        if( l == r ) return;
        const lli mid = ( l + r ) >> 1;
        tar <= mid ? insert(lson[pos],l,mid,tar) : insert(rson[pos],mid+1,r,tar);
    }
    inline int query(int pos,lli l,lli r,const lli &ll,const lli &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return sum[pos];
        const lli mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        else return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
}sgt;

int root;
lli su[maxn],L,R,ans;

int main() {
    static int n;
    scanf("%d%lld%lld",&n,&L,&R) , sgt.insert(root,-lim,lim,0);
    for(int i=1;i<=n;i++) scanf("%lld",su+i) , su[i] += su[i-1] , ans += sgt.query(root,-lim,lim,su[i]-R,su[i]-L) , sgt.insert(root,-lim,lim,su[i]);
    printf("%lld\n",ans);
    return 0;
}

