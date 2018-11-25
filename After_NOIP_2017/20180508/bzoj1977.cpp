#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=3e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int id[maxn],rec[maxn],fe[maxn];
struct SegmentTree {
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],cnt;
    struct Node {
        int mx,sec; // if mx == sec , sec = -1 .
        friend Node operator + (const Node &a,const Node &b) {
            Node ret;
            ret.mx = max( a.mx , b.mx );
            if( a.mx != b.mx ) ret.sec = min( a.mx , b.mx );
            else ret.sec = max( a.sec , b.sec );
            return ret;
        }
    }ns[maxn<<2];
    SegmentTree() { cnt = 1; }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) {
            ns[pos].mx = fe[rec[ll]] , ns[pos].sec = -1;
            return;
        } const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        ns[pos] = ns[lson[pos]] + ns[rson[pos]];
    }
    inline Node query(int pos,const int &ll,const int &rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return ns[pos];
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return query(lson[pos],ll,rr);
        else if( ll > mid ) return query(rson[pos],ll,rr);
        else return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
}sgt;
typedef SegmentTree::Node Node;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn];

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos,int f) {
    siz[pos] = 1 , fe[pos] = f;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at],l[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void dfs(int pos) {
    static int dd;
    rec[id[pos]=++dd] = pos , top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
}
inline Node chain(int x,int y) {
    Node ret = (Node){-1,-1};
    int sel = 0;
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) swap(x,y);
        ret = sel ? ret + sgt.query(1,id[top[x]],id[x]) : sgt.query(1,id[top[x]],id[x]);
        x = fa[top[x]] , sel = 1;
    }
    if( x != y ) ret = ret + sgt.query(1,min(id[x],id[y])+1,max(id[x],id[y]));
    return ret;
}

bool sel[maxe];

struct Edge {
    int u,v,val;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.val < b.val;
    }
}es[maxe];

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return x == fa[x] ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        if( ( x = findfa(x) ) != ( y = findfa(y) ) ) return fa[x] = y , 1;
        return 0;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

lli su,ans=inf;

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&es[i].u,&es[i].v,&es[i].val);
    sort(es+1,es+1+m) , ufs.init(n);
    for(int i=1;i<=m;i++) if( ( sel[i] = ufs.merge(es[i].u,es[i].v) ) ) su += es[i].val , addedge(es[i].u,es[i].v,es[i].val) , addedge(es[i].v,es[i].u,es[i].val);
    pre(1,-1) , dfs(1) , sgt.build(1,1,n);
    for(int i=1;i<=m;i++) if( !sel[i] ) {
        Node cur = chain(es[i].u,es[i].v);
        if( cur.mx != es[i].val ) ans = min( ans , (lli) es[i].val - cur.mx );
        else if( ~cur.sec ) ans = min( ans , (lli) es[i].val - cur.sec );
    }
    printf("%lld\n",su+ans);
    return 0;
}
