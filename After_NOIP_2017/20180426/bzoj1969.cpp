#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
const int maxn=3e4+1e2,maxe=1e5+1e2,maxq=4e4+1e2;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],sum[maxn<<3],fil[maxn<<3],cnt;
    SegmentTree() { memset(fil,-1,sizeof(fil)) , cnt = 1; }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return void(sum[pos]=1);
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr) , sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline void apply(int pos) {
        fil[pos] = 0 , sum[pos] = 0;
    }
    inline void push(int pos) {
        if( ~fil[pos] ) apply(lson[pos]) , apply(rson[pos]) , fil[pos] = -1;
    }
    inline void update(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return apply(pos);
        push(pos) , update(lson[pos],ll,rr) , update(rson[pos],ll,rr) , sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int query(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return 0;
        if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
        return push(pos) , query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
}sgt;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return x == fa[x] ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        return x = findfa(x) , y = findfa(y) , x == y ? 0 : fa[x] = y;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],id[maxn];
    inline void addedge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void pre(int pos) {
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pre(t[at]) , siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
    }
    inline void dfs(int pos) {
        static int iid;
        id[pos] = ++iid , top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        if( son[pos] ) dfs(son[pos]);
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
    }
    inline int querychain(int x,int y) {
        int ret = 0;
        while( top[x] != top[y] ) {
            if( dep[top[x]] < dep[top[y]] ) std::swap(x,y);
            ret += sgt.query(1,id[top[x]],id[x]) , x = fa[top[x]];
        }
        return ret + ( x != y ? sgt.query(1,std::min(id[x],id[y])+1,std::max(id[x],id[y])) : 0 );
    }
    inline void fillchain(int x,int y) {
        while( top[x] != top[y] ) {
            if( dep[top[x]] < dep[top[y]] ) std::swap(x,y);
            sgt.update(1,id[top[x]],id[x]) , x = fa[top[x]];
        }
        if( x != y ) sgt.update(1,std::min(id[x],id[y])+1,std::max(id[x],id[y]));
    }
}

struct Edge {
    int u,v; // assert u < v .
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.u != b.u ? a.u < b.u : a.v < b.v;
    }
};
std::map<Edge,int> mp;

int u[maxe],v[maxe],ban[maxe]; // ban = 1 means deleted , ban = -1 means used in tree .
int o[maxq],a[maxq],b[maxq],ans[maxq];

int main() {
    static int n,m,q;
    scanf("%d%d",&n,&m) , ufs.init(n);
    for(int i=1;i<=m;i++) scanf("%d%d",u+i,v+i) , mp[(Edge){std::min(u[i],v[i]),std::max(u[i],v[i])}] = i;
    for(int oo,ta,tb;scanf("%d",&oo)==1&&~oo;) {
        if( ! ( o[++q] = oo ) ) scanf("%d%d",&ta,&tb) , ban[ a[q] = mp[(Edge){std::min(ta,tb),std::max(ta,tb)}] ] = 1;
        else scanf("%d%d",a+q,b+q);
    }
    for(int i=1;i<=m;i++) if( !ban[i] && ufs.merge(u[i],v[i]) ) ban[i] = -1 , Tree::addedge(u[i],v[i]) , Tree::addedge(v[i],u[i]);
    Tree::pre(1) , Tree::dfs(1) , sgt.build(1,1,n);
    for(int i=1;i<=m;i++) if( !ban[i] ) Tree::fillchain(u[i],v[i]);
    for(int i=q;i;i--) {
        if( !o[i] ) Tree::fillchain(u[a[i]],v[a[i]]);
        else ans[i] = Tree::querychain(a[i],b[i]);
    }
    for(int i=1;i<=q;i++) if( o[i] ) printf("%d\n",ans[i]);
    return 0; 
}

