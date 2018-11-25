#include<cstdio>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=5e4+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],in[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],dfn[maxn],rec[maxn];
lli lazy[maxn<<3];
struct Node {
    lli mx,mi,ltr,rtl;
    inline Node rev() {
        return (Node){mx,mi,rtl,ltr};
    }
    inline void apply(const lli &x) {
        mx += x , mi += x;
    }
    friend Node operator + (const Node &a,const Node &b) {
        return (Node){max(a.mx,b.mx),min(a.mi,b.mi),max(b.mx-a.mi,max(a.ltr,b.ltr)),max(a.mx-b.mi,max(a.rtl,b.rtl))};
    }
}ns[maxn<<3];

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        ns[pos].mi = ns[pos].mx = in[rec[ll]];
        return;
    } const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline void apply(int pos,lli x) {
    lazy[pos] += x , ns[pos].apply(x);
}
inline void push(int pos) {
    if( !lazy[pos] || l[pos] == r[pos] ) return;
    apply(lson[pos],lazy[pos]) , apply(rson[pos],lazy[pos]) ,
    lazy[pos] = 0;
}
inline void update(int pos,int ll,int rr,lli x) {
    if( ll <= l[pos] && r[pos] <= rr ) return apply(pos,x);
    push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid ) update(lson[pos],ll,rr,x);
    else if( mid < ll ) update(rson[pos],ll,rr,x);
    else {
        update(lson[pos],ll,rr,x) ,
        update(rson[pos],ll,rr,x) ;
    }
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline Node query(int pos,int ll,int rr) {
    if( ll <= l[pos] && r[pos] <= rr ) return ns[pos];
    push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid ) return query(lson[pos],ll,rr);
    if( mid < ll ) return query(rson[pos],ll,rr);
    Node ql = query(lson[pos],ll,rr) , qr = query(rson[pos],ll,rr);
    return ql + qr;
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 ;
        pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void dfs(int pos) {
    static int dd;
    dfn[pos] = ++dd , rec[dd] = pos ,
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] )
        if( dep[top[x]] > dep[top[y]] ) x = fa[top[x]];
        else y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}
inline Node chain(int x,int l,int r) {
    Node ret;
    if( top[x] == top[l] ) ret = query(1,dfn[l],dfn[x]);
    else {
        ret = query(1,dfn[top[x]],dfn[x]) , x = fa[top[x]];
        while( top[x] != top[l] )  {
            ret = query(1,dfn[top[x]],dfn[x]) + ret ,
            x = fa[top[x]];
        }
        ret = query(1,dfn[l],dfn[x]) + ret;
    }
    return r ? ret.rev() : ret;
}
inline void chain_update(int x,int y,lli a) {
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) swap(x,y); // now assert dep[top[x]] >= dep[top[y]] .
        update(1,dfn[top[x]],dfn[x],a) , x = fa[top[x]];
    }
    if( dfn[x] > dfn[y] ) swap(x,y); // now assert dfn[x] <= dfn[y] .
    update(1,dfn[x],dfn[y],a);
}
inline Node query(int x,int y) {
    int l = lca(x,y);
    return chain(x,l,1) + chain(y,l,0);
}

int main() {
    static int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    pre(1) , dfs(1) , build(cnt=1,1,n);
    scanf("%d",&m) ;
    for(int i=1,a,b,x;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&x);
        printf("%lld\n",query(a,b).ltr);
        chain_update(a,b,x);
    }
    return 0;
}

