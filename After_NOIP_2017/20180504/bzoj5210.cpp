#include<cstdio>
#include<algorithm>
#include<set>
using std::max;
typedef long long int lli;
const int maxn=2e5+1e2;

lli in[maxn],f[maxn],g[maxn],idp[maxn]; // f means from chain to top , g means cost of pos and virtualsons of pos , idp means max segment sum .
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int dep[maxn],siz[maxn],fa[maxn],son[maxn],top[maxn],id[maxn],rec[maxn],mxd[maxn];
std::multiset<lli> ls[maxn];

struct SegmentTree {
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],cnt;
    SegmentTree() { cnt = 1 ; }
    struct Node {
        lli sl,sr,su,mx;
        friend Node operator + (const Node &a,const Node &b) {
            return (Node){max(a.sl,a.su+b.sl),max(a.sr+b.su,b.sr),a.su+b.su,max(a.sr+b.sl,max(a.mx,b.mx))};
        }
        inline void fil(int id) {
            sl = sr = max( g[rec[id]] , 0ll ) , su = g[rec[id]] , mx = max( g[rec[id]] , *ls[rec[id]].rbegin() );
        }
    }ns[maxn<<2];
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return ns[pos].fil(ll);
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr) ,
        ns[pos] = ns[lson[pos]] + ns[rson[pos]];
    }
    inline void update(int pos,const int &tar) {
        if( l[pos] == r[pos] ) return ns[pos].fil(tar);
        const int mid = ( l[pos] + r[pos] ) >> 1;
        tar <= mid ? update(lson[pos],tar) : update(rson[pos],tar);
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

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pr(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pr(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void pre(int pos) {
    static int iid;
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos , rec[id[pos]=++iid] = pos , mxd[top[pos]] = iid , g[pos] = in[pos];
    if( son[pos] ) pre(son[pos]) , idp[pos] = idp[son[pos]] , f[pos] = f[son[pos]];
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) pre(t[at]) , g[pos] += f[t[at]] , ls[pos].insert(idp[t[at]]);
    f[pos] = max( f[pos] + g[pos] , 0ll ) , idp[pos] = max( idp[pos] , max( f[pos] , *ls[pos].rbegin() ) );
}

inline Node query(int pos) {
    return sgt.query(1,id[pos],mxd[top[pos]]);
}
inline void update(int pos,int nv) {
    Node od,nw;
    int fst = 1;
    od.sl = in[pos] , nw.sl = nv , in[pos] = nv;
    while(pos) {
        g[pos] += nw.sl - od.sl;
        if( !fst ) ls[pos].erase(ls[pos].find(od.mx)) , ls[pos].insert(nw.mx);
        od = sgt.query(1,id[top[pos]],mxd[top[pos]]) , sgt.update(1,id[pos]) , nw = sgt.query(1,id[top[pos]],mxd[top[pos]]);
        fst = 0 , pos = fa[top[pos]];
    }
}

int main() {
    static int n,m;
    static char o[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",in+i) , ls[i].insert(0);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    pr(1) , pre(1);
    sgt.build(1,1,n);
    for(int i=1,x,y;i<=m;i++) {
        scanf("%s%d",o,&x);
        if( *o == 'M' ) scanf("%d",&y) , update(x,y);
        else printf("%lld\n",query(x).mx);
    }
    return 0;
}
