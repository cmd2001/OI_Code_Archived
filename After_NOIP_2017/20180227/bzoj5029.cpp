#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=3e5+1e2;

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],col[maxn<<3],lazy[maxn<<3],cnt;
int x[maxn/3],y[maxn/3],pts[maxn],vis[maxn/3],len,ans;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
}
inline void fill(int pos,int x) {
    if( !pos ) return;
    col[pos] = lazy[pos] = x;
}
inline void push(int pos) {
    if( ~lazy[pos] ) {
        fill(lson[pos],lazy[pos]) ,
        fill(rson[pos],lazy[pos]) ,
        lazy[pos] = -1;
    }
}
inline void update(int pos,int ll,int rr,int x) {
    if( rr < l[pos] || r[pos] < ll ) return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        fill(pos,x);
        return;
    }
    push(pos);
    update(lson[pos],ll,rr,x) , update(rson[pos],ll,rr,x);
}
inline void dfs(int pos) {
    if( !pos ) return;
    if( l[pos] == r[pos] && !vis[col[pos]] ) ans += ( vis[col[pos]] = 1 );
    push(pos) , dfs(lson[pos]) , dfs(rson[pos]);
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",x+i,y+i) , pts[++len] = x[i] , pts[++len] = y[i] , pts[++len] = y[i] + 1;
    std::sort(pts+1,pts+1+len) , len = std::unique(pts+1,pts+1+len) - pts - 1;
    memset(lazy,-1,sizeof(lazy)) , build(cnt=1,1,len);
    for(int i=1;i<=n;i++) {
        x[i] = std::lower_bound(pts+1,pts+1+len,x[i]) - pts,
        y[i] = std::lower_bound(pts+1,pts+1+len,y[i]) - pts;
        update(1,x[i],y[i],i);
    }
    dfs(1);
    if( *vis ) --ans;
    printf("%d\n",ans);
    return 0;
}
