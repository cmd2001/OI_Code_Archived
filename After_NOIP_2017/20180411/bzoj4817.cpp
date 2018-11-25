#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int ini[maxn],dfn[maxn],rit[maxn],dd;

struct ChainDividedTree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn];
    inline void coredge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void pre(int pos) {
        siz[pos] = 1 , ini[rit[pos]=dfn[pos]=++dd] = dep[pos] + 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , 
            pre(t[at]) , siz[pos] += siz[t[at]] , rit[pos] = rit[t[at]] ,
            son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
    }
    inline void dfs(int pos) {
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs(t[at]);
    }
    inline int lca(int x,int y) {
        while( top[x] != top[y] )
            if( dep[top[x]] > dep[top[y]] ) x = fa[top[x]];
            else y = fa[top[y]];
        return dep[x] < dep[y] ? x : y;
    }
}tree;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],mx[maxn<<3],lazy[maxn<<3],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return void(mx[pos]=ini[ll]);
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] );
    }
    inline void apply(int pos,int val) {
        if( !pos ) return;
        mx[pos] += val , lazy[pos] += val;
    }
    inline void push(int pos) {
        if( lazy[pos] ) {
            apply(lson[pos],lazy[pos]) , apply(rson[pos],lazy[pos]) ,
            lazy[pos] = 0;
        }
    }
    inline void update(int pos,int ll,int rr,int val) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return apply(pos,val);
        push(pos);
        update(lson[pos],ll,rr,val) , update(rson[pos],ll,rr,val);
        mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] );
    }
    inline int query(int pos,int ll,int rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return mx[pos];
        push(pos);
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return query(lson[pos],ll,rr);
        else if( ll > mid ) return query(rson[pos],ll,rr);
        return max( query(lson[pos],ll,rr) , query(rson[pos],ll,rr) );
    }
    inline void updatesub(int pos,int val) {
        update(1,dfn[pos],rit[pos],val);
    }
    inline int querypoint(int pos) {
        return query(1,dfn[pos],dfn[pos]);
    }
    inline int querysub(int pos) {
        return query(1,dfn[pos],rit[pos]);
    }
}segt;

struct LinkCutTree {
    int ch[maxn][2],fa[maxn];
    inline bool isroot(int x) {
        return x != ch[fa[x]][0] && x != ch[fa[x]][1];
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isroot(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
    }
    inline void splay(int x) {
        while( !isroot(x) ) {
            if( !isroot(fa[x]) ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline int findleft(int x) {
        while( ch[x][0] ) x = ch[x][0];
        return x;
    }
    inline void access(int x) {
        int t = 0;
        while(x) {
            splay(x);
            if( ch[x][1] ) segt.updatesub(findleft(ch[x][1]),1);
            if( t ) segt.updatesub(findleft(t),-1);
            ch[x][1] = t , t = x , x = fa[x];
        }
    }
}lct;

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , tree.addedge(a,b);
    tree.pre(1) , tree.dfs(1);
    segt.build(segt.cnt=1,1,n);
    for(int i=2;i<=n;i++) lct.fa[i] = tree.fa[i];
    for(int i=1,o,x,y;i<=m;i++) {
        scanf("%d%d",&o,&x);
        if( o == 2 ) scanf("%d",&y);
        if( o == 1 ) lct.access(x);
        else if( o == 2 ) printf("%d\n",segt.querypoint(x)+segt.querypoint(y)-2*segt.querypoint(tree.lca(x,y))+1);
        else if( o == 3 ) printf("%d\n",segt.querysub(x));
    }
    return 0;
}
