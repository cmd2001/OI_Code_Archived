#include<cstdio>
using namespace std;
const int maxn=5e5+1e2,maxd=1.5e7+1e2;

int lson[maxd],rson[maxd],sum[maxd],cnt;
int in[maxn],root[maxn];

inline void prebuild(int pos,int ll,int rr) {
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    prebuild(lson[pos]=++cnt,ll,mid);
    prebuild(rson[pos]=++cnt,mid+1,rr);
}
inline void insert(int pos,int pre,int l,int r,int tar) {
    lson[pos] = lson[pre] , rson[pos] = rson[pre];
    if( l == r ) {
        sum[pos] = sum[pre] + 1;
        return;
    }
    const int mid = ( l + r ) >> 1;
    if( tar <= mid ) insert(lson[pos]=++cnt,lson[pre],l,mid,tar);
    else insert(rson[pos]=++cnt,rson[pre],mid+1,r,tar);
    sum[pos] = sum[lson[pos]] + sum[rson[pos]];
}
inline int query(int pos,int pre,int l,int r,int lim) {
    if( l == r )
        return l;
    int sl = sum[lson[pos]] - sum[lson[pre]] , sr = sum[rson[pos]] - sum[rson[pre]];
    const int mid = ( l + r ) >> 1;
    if( sl > lim ) return query(lson[pos],lson[pre],l,mid,lim);
    else if( sr > lim ) return query(rson[pos],rson[pre],mid+1,r,lim);
    return 0;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    prebuild(root[0]=++cnt,1,n);
    for(int i=1;i<=n;i++)
        insert(root[i]=++cnt,root[i-1],1,n,in[i]);
    for(int i=1,l,r;i<=m;i++) {
        scanf("%d%d",&l,&r);
        printf("%d\n",query( root[r] , root[l-1] , 1 , n , (r-l+1)>>1 ) );
    }
    
    return 0;
}