#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cmath>
#define lli long long int
const int maxn=1e5+1e2;

int col[maxn],w[maxn],v[maxn];
int dfn[maxn],rit[maxn],id[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn];
int bel[maxn<<1];
int tim[maxn],vis[maxn];
lli ans[maxn],now;
int n,l,r,tm;

struct QNode {
    int l,r,t,id;
    friend bool operator < (const QNode &a,const QNode &b) {
        return bel[rit[a.l]] != bel[rit[b.l]] ? bel[rit[a.l]] < bel[rit[b.l]] : dfn[a.r] < dfn[b.r];
    }
}qs[maxn];
struct MNode {
    int pos,nw,od;
}ms[maxn];

int s[maxn],t[maxn<<1],nxt[maxn<<1];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    static int dd;
    siz[pos] = 1 , dfn[pos] = ++dd , id[dd] = pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos ,
        pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
    rit[pos] = ++dd , id[dd] = pos;
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
inline void mp(int pos) {
    if( vis[pos] ) now -= (lli) v[col[pos]] * w[tim[col[pos]]--];
    else now += (lli) v[col[pos]] * w[++tim[col[pos]]];
    vis[pos] ^= 1;
}
inline void mc(int pos,int nw) {
    int jud = vis[pos];
    if( jud ) mp(pos);
    col[pos] = nw;
    if( jud ) mp(pos);
}
inline void query(const QNode &q) {
    while( tm < q.t ) ++tm , mc(ms[tm].pos,ms[tm].nw);
    while( q.t < tm ) mc(ms[tm].pos,ms[tm].od) , --tm;
    int tarl,tarr=dfn[q.r];
    const int lc = lca( q.l , q.r );
    if( lc == q.l ) tarl = dfn[q.l];
    else tarl = rit[q.l];
    while( tarl < l ) mp(id[--l]);
    while( l < tarl ) mp(id[l++]);
    while( r < tarr ) mp(id[++r]);
    while( tarr < r ) mp(id[r--]);
    if( lc != q.l ) mp(lc);
    ans[q.id] = now;
    if( lc != q.l ) mp(lc);
}
inline void initblk() {
    int blksiz = (int)( pow(n,2.0/3)+0.5 ) , cnt = 0;
    for(int l=1,r;l<=(n<<1);l=r+1) {
        r = std::min( l + blksiz - 1 , n << 1 ) , ++cnt;
        for(int k=l;k<=r;k++) bel[k] = cnt;
    }
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int m,q,cntq,cntm;
    n = getint() , m = getint() , q = getint();
    for(int i=1;i<=m;i++) v[i] = getint();
    for(int i=1;i<=n;i++) w[i] = getint();
    for(int i=1,a,b;i<n;i++) {
        a = getint() , b = getint() ,
        addedge(a,b) , addedge(b,a);
    }
    for(int i=1;i<=n;i++) col[i] = getint();
    pre(1) , dfs(1);
    for(int i=1,tpe,x,y;i<=q;i++) {
        tpe = getint() , x = getint() , y = getint();
        if( !tpe ) {
            ms[++cntm] = (MNode){x,y,col[x]};
            col[x] = y;
        } else {
            if( dfn[x] > dfn[y] ) std::swap(x,y);
            ++cntq;
            qs[cntq] = (QNode){x,y,cntm,cntq};
        }
    }
    for(int i=cntm;i;i--) col[ms[i].pos] = ms[i].od;
    initblk() , std::sort(qs+1,qs+1+cntq);
    tm = 0 , l = r = 1 , mp(1);
    for(int i=1;i<=cntq;i++) query(qs[i]);
    for(int i=1;i<=cntq;i++) printf("%lld\n",ans[i]);
    return 0;
}

/*#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<cmath>
#include<cassert>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int col[maxn],w[maxn],v[maxn];
int dfn[maxn],rit[maxn],id[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn];
int bel[maxn<<1];
int tim[maxn],vis[maxn];
lli ans[maxn],now;
int n,l,r,tm;

struct QNode {
    int l,r,t,id;
    friend bool operator < (const QNode &a,const QNode &b) {
        return bel[rit[a.l]] != bel[rit[b.l]] ? bel[rit[a.l]] < bel[rit[b.l]] : dfn[a.r] < dfn[b.r];
    }
}qs[maxn];
struct MNode {
    int pos,nw,od;
}ms[maxn];

int s[maxn],t[maxn<<1],nxt[maxn<<1];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    static int dd;
    siz[pos] = 1 , dfn[pos] = ++dd , id[dd] = pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos ,
        pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
    rit[pos] = ++dd , id[dd] = pos;
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
inline void mp(int pos) {
    if( vis[pos] ) now -= (lli) v[col[pos]] * w[tim[col[pos]]--];
    else now += (lli) v[col[pos]] * w[++tim[col[pos]]];
    vis[pos] ^= 1;
}
inline void mc(int pos,int nw) {
    int jud = vis[pos];
    if( jud ) mp(pos);
    col[pos] = nw;
    if( jud ) mp(pos);
}
inline void query(const QNode &q) {
    //debug<<"in query"<<endl;
    //debug<<q.l<<" "<<q.r<<" "<<q.t<<endl;
    while( tm < q.t ) ++tm , mc(ms[tm].pos,ms[tm].nw);
    while( q.t < tm ) mc(ms[tm].pos,ms[tm].od) , --tm;
    //debug<<"tm modified"<<endl;
    int tarl,tarr=dfn[q.r];
    const int lc = lca( q.l , q.r );
    //debug<<"lca = "<<lc<<endl;
    if( lc == q.l ) tarl = dfn[q.l];
    else tarl = rit[q.l];
    //debug<<"tarx = "<<tarl<<"tary = "<<tarr<<endl;
    while( tarl < l ) mp(id[--l]);
    while( l < tarl ) mp(id[l++]);
    while( r < tarr ) mp(id[++r]);
    while( tarr < r ) mp(id[r--]);
    //debug<<"l , r modified"<<endl;
    if( lc == q.r && q.l != q.r ) cerr<<"Assertion failed!"<<endl,exit(0);
    if( lc != q.l ) mp(lc);
    ans[q.id] = now;
    if( lc != q.l ) mp(lc);
}
inline void initblk() {
    int blksiz = (int)( pow(n,2.0/3)+0.5 ) , cnt = 0;
    for(int l=1,r;l<=(n<<1);l=r+1) {
        r = min( l + blksiz - 1 , n << 1 ) , ++cnt;
        for(int k=l;k<=r;k++) bel[k] = cnt;
    }
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int m,q,cntq,cntm;
    n = getint() , m = getint() , q = getint();
    for(int i=1;i<=m;i++) v[i] = getint();
    for(int i=1;i<=n;i++) w[i] = getint();
    for(int i=1,a,b;i<n;i++) {
        a = getint() , b = getint() ,
        addedge(a,b) , addedge(b,a);
    }
    for(int i=1;i<=n;i++) col[i] = getint();
    pre(1) , dfs(1);
    for(int i=1,tpe,x,y;i<=q;i++) {
        tpe = getint() , x = getint() , y = getint();
        if( !tpe ) {
            ms[++cntm] = (MNode){x,y,col[x]};
            col[x] = y;
        } else {
            if( dfn[x] > dfn[y] ) swap(x,y);
            ++cntq;
            qs[cntq] = (QNode){x,y,cntm,cntq};
        }
    }
    for(int i=cntm;i;i--) col[ms[i].pos] = ms[i].od;
    //for(int i=1;i<=n;i++) debug<<col[i]<<" ";debug<<endl;
    initblk() , sort(qs+1,qs+1+cntq);
    tm = 0 , l = r = 1 , mp(1);
    for(int i=1;i<=cntq;i++) query(qs[i]);
    for(int i=1;i<=cntq;i++) printf("%lld\n",ans[i]);
    return 0;
}*/
