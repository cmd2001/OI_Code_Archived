#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=1e5+1e2,maxe=5e6+1e2;

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int &pos,int pre,int l,int r,const int &tar) {
        sum[pos=++cnt] = sum[pre] + 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return sum[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
}pst;

int fst[maxn],sec[maxn],root[maxn],n;
lli ans;

int main() {
    scanf("%d",&n) , memset(fst,-1,sizeof(fst)) , memset(sec,-1,sizeof(sec));
    for(int i=1,t;i<=n<<1;i++) {
        scanf("%d",&t);
        if( !~fst[t] ) fst[t] = i;
        else sec[fst[t]] = i;
    }
    for(int i=1;i<=n<<1;i++) {
        root[i] = root[i-1];
        if( ~sec[i] ) ans += pst.query(root[i],1,n<<1,i+1,sec[i]-1) , pst.insert(root[i],root[i],1,n<<1,sec[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
