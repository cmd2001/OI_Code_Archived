#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
//#define debug cerr
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=3e5+1e2,maxb=4e2+1e2;

#ifdef debug
int logfa,logfq;
#endif

int n,bs;

struct pii{int l,r;};
struct RotatelessTreap {
    int lson[maxn],rson[maxn],dat[maxn],mx[maxn],fix[maxn];
    lli pv[maxn];
    RotatelessTreap() {
        for(int i=0;i<maxn;i++) fix[i] = i;
        random_shuffle(fix,fix+maxn);
    }
    inline void maintain(int pos) {
        mx[pos] = max( dat[pos] , max(mx[lson[pos]],mx[rson[pos]]) );
    }
    inline pii split(int pos,lli nv) { // left is <= nv .
        if( !pos ) return (pii){0,0};
        if( pv[pos] > nv ) { // split pos to right .
            pii spl = split(lson[pos],nv);
            lson[pos] = spl.r , maintain(pos);
            return (pii){spl.l,pos};
        } else {
            pii spr = split(rson[pos],nv);
            rson[pos] = spr.l , maintain(pos);
            return (pii){pos,spr.r};
        }
    }
    inline int merge(int x,int y) {
        if( !x || !y ) return x | y;
        if( fix[x] > fix[y] ) {
            rson[x] = merge(rson[x],y) , maintain(x);
            return x;
        } else {
            lson[y] = merge(x,lson[y]) , maintain(y);
            return y;
        }
    }
    inline void reset(int pos,lli p,int d) {
        lson[pos] = rson[pos] = 0 , pv[pos] = p , dat[pos] = mx[pos] = d;
    }
    inline void insert_node(int &root,int t) {
        pii sp = split(root,pv[t]);
        root = merge(sp.l,merge(t,sp.r));
    }
    inline pii query_seg(int &root,lli ll,lli rr) { // return pair<(bool)siz,max> of segment (ll,rr] .
        pii spl = split(root,ll) , spr = split(spl.r,rr);
        pii ret = (pii){spr.l,mx[spr.l]};
        root = merge(spl.l,merge(spr.l,spr.r));
        return ret;
    }
}treap;

int iw[maxn],ib[maxn];
int bel[maxn],st[maxb],ed[maxb],lazy_w[maxb],lazy_b[maxb],root[maxb];

inline lli gid(int pos,int st,int iw) { // iw can't be zero .
    return (lli) iw * bs + pos - st;
}
inline void rebuild_blk(int id) {
    root[id] = 0;
    for(int i=st[id];i<=ed[id];i++) {
        treap.reset(i,gid(i,st[id],iw[i]),ib[i]) , treap.insert_node(root[id],i);
    }
}
inline void push_all(int id) {
    if( ~lazy_w[id] ) {
        for(int i=st[id];i<=ed[id];i++) iw[i] = lazy_w[id];
        lazy_w[id] = -1;
    }
    if( ~lazy_b[id] ) {
        for(int i=st[id];i<=ed[id];i++) ib[i] = lazy_b[id];
        lazy_b[id] = -1;
    }
}
inline void full_apply_w(int id,int w) {
    #ifdef debug
    ++logfa;
    #endif
    lazy_w[id] = w;
}
inline void full_apply_b(int id,int b) {
    #ifdef debug
    ++logfa;
    #endif
    lazy_b[id] = b;
}
inline int full_query(int id,int l,int r) {
    #ifdef debug
    ++logfq;
    #endif
    if( ~lazy_w[id] ) {
        if( ! ( l <= lazy_w[id] && lazy_w[id] <= r ) ) return 0;
        if( ~lazy_b[id] ) return lazy_b[id];
        return treap.mx[root[id]];
    } else {
        lli ll = (lli) bs * l - 1 , rr = (lli) bs * ( r + 1 ) - 1;
        pii t = treap.query_seg(root[id],ll,rr);
        if( ~lazy_b[id] ) return t.l ? lazy_b[id] : 0;
        else return t.r;
    }
}
inline void part_apply_w(int id,int w,int l,int r) {
    push_all(id) , l = max( l , st[id] ) , r = min( r , ed[id] );
    for(int i=l;i<=r;i++) iw[i] = w;
    rebuild_blk(id);
}
inline void part_apply_b(int id,int b,int l,int r) {
    push_all(id) , l = max( l , st[id] ) , r = min( r , ed[id] );
    for(int i=l;i<=r;i++) ib[i] = b;
    rebuild_blk(id);
}
inline int part_query(int id,int l,int r,int segl,int segr) {
    segl = max( segl , st[id] ) , segr = min( segr , ed[id] );
    if( ~lazy_w[id] ) {
        if( ! ( l <= lazy_w[id] && lazy_w[id] <= r ) ) return 0;
        if( ~lazy_b[id] ) return lazy_b[id];
        int ret = 0;
        for(int i=segl;i<=segr;i++) ret = max( ret , ib[i] );
        return ret;
    } else {
        if( ~lazy_b[id] ) {
            for(int i=segl;i<=segr;i++) if( l <= iw[i] && iw[i] <= r ) return lazy_b[id];
            return 0;
        } else {
            int ret = 0;
            for(int i=segl;i<=segr;i++) if( l <= iw[i] && iw[i] <= r ) ret = max( ret , ib[i] );
            return ret;
        }
    }
}
inline int query_seg(int l,int r,int ll,int rr) { // ll , rr is value segment .
    if( bel[l] == bel[r] ) return part_query(bel[l],ll,rr,l,r);
    else {
        int ret = max( part_query(bel[l],ll,rr,l,r) , part_query(bel[r],ll,rr,l,r) );
        for(int i=bel[l]+1;i<bel[r];i++) ret = max( ret , full_query(i,ll,rr) );
        return ret;
    }
}
inline void apply_seg_w(int l,int r,int w) {
    if( bel[l] == bel[r] ) return part_apply_w(bel[l],w,l,r);
    else {
        part_apply_w(bel[l],w,l,r) , part_apply_w(bel[r],w,l,r);
        for(int i=bel[l]+1;i<bel[r];i++) full_apply_w(i,w);
    }
}
inline void apply_seg_b(int l,int r,int b) {
    if( bel[l] == bel[r] ) return part_apply_b(bel[l],b,l,r);
    else {
        part_apply_b(bel[l],b,l,r) , part_apply_b(bel[r],b,l,r);
        for(int i=bel[l]+1;i<bel[r];i++) full_apply_b(i,b);
    }
}

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn],dfn[maxn],rit[maxn];

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void dfs(int pos) {
    static int dd;
    dfn[pos] = ++dd , top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
    rit[pos] = dd;
}

inline void apply_subtree_w(int pos,int w) {
    apply_seg_w(dfn[pos],rit[pos],w);
}
inline void apply_subtree_b(int pos,int b) {
    apply_seg_b(dfn[pos],rit[pos],b);
}
inline int query_chain(int x,int y,int ll,int rr) {
    int ret = 0;
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) swap(x,y);
        ret = max( ret , query_seg(dfn[top[x]],dfn[x],ll,rr) ) , x = fa[top[x]];
    }
    ret = max( ret , query_seg(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),ll,rr) );
    return ret;
}

inline void initblk() {
    bs = sqrt(n);
    for(int l=1,r,cnt=0;l<=n;l=r+1) {
        r = min( l + bs - 1 , n ) , st[++cnt] = l , ed[cnt] = r , lazy_w[cnt] = lazy_b[cnt] = -1;
        for(int i=l;i<=r;i++) bel[i] = cnt;
        rebuild_blk(cnt);
    }
}

int srt[maxn<<2],len;
int o[maxn],ox[maxn],oy[maxn],oll[maxn],orr[maxn];

inline int gid(int x) {
    return lower_bound(srt+1,srt+1+len,x) - srt;
}

int main() {
    static int m;
    static char ooo[50];
    freopen("rabit.in","r",stdin);
    freopen("rabit.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    for(int i=1;i<=m;i++) {
        scanf("%s%d%d",ooo+1,ox+i,oy+i);
        if( ooo[1] == 'C' ) {
            if( ooo[7] == 'W' ) o[i] = 1 , srt[++len] = oy[i];
            else o[i] = 2;
        } else o[i] = 3 , scanf("%d%d",oll+i,orr+i) , srt[++len] = oll[i] , srt[++len] = orr[i]; 
    }
    #ifdef debug
    debug<<"all readed"<<endl;
    #endif
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=m;i++) {
        if( o[i] == 1 ) oy[i] = gid(oy[i]);
        else if( o[i] == 3 ) oll[i] = gid(oll[i]) , orr[i] = gid(orr[i]);
    }
    #ifdef debyg
    debug<<"sorted"<<endl;
    #endif
    pre(1) , dfs(1) , initblk();
    #ifdef debug
    debug<<"inited"<<endl;
    #endif
    for(int i=1;i<=m;i++) {
        if( o[i] == 1 ) apply_subtree_w(ox[i],oy[i]);
        else if( o[i] == 2 ) apply_subtree_b(ox[i],oy[i]);
        else printf("%d\n",query_chain(ox[i],oy[i],oll[i],orr[i]));
    }
    #ifdef debug
    debug<<"logfa = "<<logfa<<"logfq = "<<logfq<<endl;
    #endif
    fclose(stdout);
    return 0;
}

