#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<cassert>
using namespace std;
const int maxn=5e4+1e2,maxb=330;

struct BlockedArray {
    int dat[maxn<<1],bel[maxn<<1],st[maxb],ed[maxb],su[maxb],cnt;
    inline void update(int pos,int x) {
        assert( dat[pos] + x >= 0 );
        if( !dat[pos] && ( dat[pos] + x ) ) ++su[bel[pos]];
        else if( dat[pos] && ! ( dat[pos] + x ) ) --su[bel[pos]];
        dat[pos] += x;
    }
    inline int query() {
        for(int i=1;i<=cnt;i++) if( su[i] != ed[i] - st[i] + 1 ) {
            for(int j=st[i];j<=ed[i];j++) if( !dat[j] ) return j;
            assert(0);
        }
        assert(0);
    }
    inline void init(int n) {
        const int sq = sqrt(n);
        for(int l=0,r;l<=n;l=r+1) {
            st[++cnt] = l , ed[cnt] = r = min( l + sq - 1 , n );
            for(int i=l;i<=r;i++) bel[i] = cnt;
        }
    }
}ba;

int in[maxn],bkup[maxn],ans[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int dep[maxn],fa[maxn],siz[maxn],son[maxn],top[maxn];
int dfn[maxn],rit[maxn],id[maxn<<1],bel[maxn<<1];
bool sel[maxn];
int n,m,mcnt,qcnt,lp,rp,mcur;

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void pre(int pos) {
    static int dd;
    id[dfn[pos]=++dd] = pos , siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]);
        siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
    }
    id[rit[pos]=++dd] = pos;
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}

struct Query {
    int l,r,t,id;
    friend bool operator < (const Query &a,const Query &b) {
        return bel[rit[a.l]] != bel[rit[b.l]] ? bel[rit[a.l]] < bel[rit[b.l]] : dfn[a.r] < dfn[b.r];
    }
}qs[maxn];
struct Modify {
    int pos,tme,nv,ov;
    friend bool operator < (const Modify &a,const Modify &b) {
        return a.tme < b.tme;
    }
}ms[maxn];

inline void rev_Node(int pos) {
    ba.update(in[pos],sel[pos]?-1:1) , sel[pos] ^= 1;
}
inline void apply_Modify(const Modify &m) {
    if( sel[m.pos] ) rev_Node(m.pos) , in[m.pos] = m.nv , rev_Node(m.pos);
    else in[m.pos] = m.nv;
}
inline void roll_Modify(const Modify &m) {
    if( sel[m.pos] ) rev_Node(m.pos) , in[m.pos] = m.ov , rev_Node(m.pos);
    else in[m.pos] = m.ov;
}
inline void solve_Modify(int tar) {
    while( mcur < mcnt && ms[mcur+1].tme <= tar ) apply_Modify(ms[++mcur]);
    while( mcur && ms[mcur].tme > tar ) roll_Modify(ms[mcur--]);
}

inline void solve_Query(const Query &q) {
    solve_Modify(q.t);
    const int lc = lca(q.l,q.r);
    const int tarl = lc == q.l ? dfn[q.l] : rit[q.l] , tarr = dfn[q.r];
    while( tarl < lp ) rev_Node(id[--lp]);
    while( rp < tarr ) rev_Node(id[++rp]);
    while( lp < tarl ) rev_Node(id[lp++]);
    while( tarr < rp ) rev_Node(id[rp--]);
    if( lc != q.l && lc != q.r ) rev_Node(lc);
    ans[q.id] = ba.query();
    if( lc != q.l && lc != q.r ) rev_Node(lc);
}

inline void initblk(int n) {
    const int bs = ceil(pow(n,2.0/3));
    for(int l=1,r,cnt=0;l<=n;l=r+1) {
        r = min( n , l + bs - 1 ) , ++cnt;
        for(int i=l;i<=r;i++) bel[i] = cnt;
    }
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) bkup[i] = in[i] = min( getint() , n );
    for(int i=1;i<n;i++) addedge(getint(),getint());
    pre(1) , dfs(1) , ba.init(n);
    for(int i=1,o,u,v;i<=m;i++) {
        o = getint() , u = getint() , v = getint();
        if( !o ) ms[++mcnt] = (Modify){u,i,min(v,n),in[u]} , in[u] = v;
        else {
            if( dfn[u] > dfn[v] ) swap(u,v);
            ++qcnt , qs[qcnt] = (Query){u,v,i,qcnt};
        }
    }
    initblk(n<<1) , stable_sort(qs+1,qs+1+qcnt);
    memcpy(in+1,bkup+1,n<<2) , lp = rp = 1 , rev_Node(id[1]);
    for(int i=1;i<=qcnt;i++) solve_Query(qs[i]);
    for(int i=1;i<=qcnt;i++) printf("%d\n",ans[i]);
    return 0;
}
