#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e5+1e2,maxe=4e6+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],dfn[maxn];
int lson[maxe],rson[maxe],mx[maxe],cnt;
lli sum[maxe];
int roots[maxn],w[maxn],c[maxn];
int n,m;

inline void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to) {
    coredge(from,to) , coredge(to,from);
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos;
            pre(t[at]) , siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
}
inline void dfs(int pos) {
    static int dd;
    dfn[pos] = ++dd;
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] && t[at] != son[pos] )
            dfs(t[at]);
}
inline void update(int pos,int l,int r,const int &tar,const int &x) {
    if( l == r ) {
        sum[pos] = mx[pos] = x;
        return;
    }
    const int mid = ( l + r ) >> 1;
    if( tar <= mid ) {
        if( !lson[pos] ) lson[pos] = ++cnt;
        update(lson[pos],l,mid,tar,x);
    } else {
        if( !rson[pos] ) rson[pos] = ++cnt;
        update(rson[pos],mid+1,r,tar,x);
    }
    mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] ) ,
    sum[pos] = sum[lson[pos]] + sum[rson[pos]];
}
inline int query_mx(int pos,int l,int r,int ll,int rr) {
    if( !pos ) return 0;
    if( ll <= l && r <= rr ) return mx[pos];
    const int mid = ( l + r ) >> 1;
    if( rr <= mid ) return query_mx(lson[pos],l,mid,ll,rr);
    if( ll > mid ) return query_mx(rson[pos],mid+1,r,ll,rr);
    return max( query_mx(lson[pos],l,mid,ll,rr) , query_mx(rson[pos],mid+1,r,ll,rr) );
}
inline lli query_sum(int pos,int l,int r,int ll,int rr) {
    if( !pos ) return 0;
    if( ll <= l && r <= rr ) return sum[pos];
    const int mid = ( l + r ) >> 1;
    if( rr <= mid ) return query_sum(lson[pos],l,mid,ll,rr);
    if( ll > mid ) return query_sum(rson[pos],mid+1,r,ll,rr);
    return query_sum(lson[pos],l,mid,ll,rr) + query_sum(rson[pos],mid+1,r,ll,rr);
}
inline int chain_mx(int x,int y,int rt) {
    int ret = 0;
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) swap(x,y); // now asset dep[top[x]] >= dep[top[y]] .
        ret = max( ret , query_mx(rt,1,n,dfn[top[x]],dfn[x]) );
        x = fa[top[x]];
    }
    if( dfn[x] > dfn[y] ) swap(x,y); // assert dfn[x] <= dfn[y] .
    ret = max( ret , query_mx(rt,1,n,dfn[x],dfn[y]) );
    return ret;
}
inline lli chain_sum(int x,int y,int rt) {
    lli ret = 0;
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) swap(x,y);
        ret += query_sum(rt,1,n,dfn[top[x]],dfn[x]);
        x = fa[top[x]];
    }
    if( dfn[x] > dfn[y] ) swap(x,y);
    ret += query_sum(rt,1,n,dfn[x],dfn[y]);
    return ret;
}

int main() {
    static char o[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",w+i,c+i);
    for(int i=1,x,y;i<n;i++) scanf("%d%d",&x,&y) , doubledge(x,y);
    pre(1) , dfs(1);
    for(int i=1;i<=n;i++) {
        if( !roots[c[i]] ) roots[c[i]] = ++cnt;
        update(roots[c[i]],1,n,dfn[i],w[i]);
    }
    for(int i=1,x,y;i<=m;i++) {
        scanf("%s%d%d",o,&x,&y);
        if( *o == 'Q' ) {
            if( o[1] == 'S' ) printf("%lld\n",chain_sum(x,y,roots[c[x]]));
            else if( o[1] == 'M' ) printf("%d\n",chain_mx(x,y,roots[c[x]]));
        } else if( *o == 'C' ) {
            if( o[1] == 'W' ) update(roots[c[x]],1,n,dfn[x],y) , w[x] = y;
            else if( o[1] == 'C' ) {
                update(roots[c[x]],1,n,dfn[x],0);
                if( !roots[y] ) roots[y] = ++cnt;
                update(roots[y],1,n,dfn[x],w[x]) , c[x] = y;
            }
        }
    }
    return 0;
}
