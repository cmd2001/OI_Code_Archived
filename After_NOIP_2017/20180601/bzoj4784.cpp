#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<cctype>
typedef long long int lli;
const int maxn=5e5+1e2,maxe=1e6+1e2;
const int mod=998244353;

__inline int add(const int &a,const int &b) {
    const int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
__inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}
__inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}

int u[maxe],v[maxe];
bool sel[maxe],su[maxe],fail;
int n,m;

namespace JudgeTree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],r[maxn<<1],cnt;
    int fa[maxn],siz[maxn],son[maxn],top[maxn],dep[maxn],delta[maxn];
    __inline void coredge(int from,int to,int rec) {
        t[++cnt] = to , r[cnt] = rec , nxt[cnt] = s[from] , s[from] = cnt;
    }
    __inline void addedge(int a,int b,int rec) {
        coredge(a,b,rec) , coredge(b,a,rec);
    }
    inline void pre1(int pos) {
        siz[pos] = 1 , son[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre1(t[at]) , siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
    }
    inline void pre2(int pos) {
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) pre2(t[at]);
    }
    inline void dfs(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            dfs(t[at]) , delta[pos] += delta[t[at]] , su[r[at]] = delta[t[at]];
            if( delta[t[at]] > 1 ) fail = 1;
        }
    }
    __inline int lca(int x,int y) {
        while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
        return dep[x] < dep[y] ? x : y;
    }
    __inline void relink(int x,int y) {
        int lc = lca(x,y);
        if( lc == x || lc == y ) --delta[lc] , ++delta[lc==x?y:x];
        else ++delta[x] , ++delta[y] , delta[lc] -= 2;
    }
    __inline void reset() {
        memset(s+1,0,n<<2) , memset(delta+1,0,n<<2) , cnt = 0;
    }
}

namespace DPTree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
    int f[maxn],g[maxn];
    bool vis[maxn];
    __inline void coredge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    __inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void dfs(int pos,int fa) {
        int su = 0; f[pos] = vis[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) ++su , dfs(t[at],pos) , mule(f[pos],f[t[at]]);
        mule(f[pos],g[su+(fa!=-1)]);
    }
    __inline int getans() {
        int ret = 1;
        g[0] = g[1] = 1;
        for(int i=2;i<=n+1;i++) g[i] = add(g[i-1],mul(g[i-2],i-1));
        for(int i=1;i<=n;i++) if( !vis[i] ) dfs(i,-1) , mule(ret,f[i]);
        return ret;
    }
    __inline void reset() {
        memset(s+1,0,n<<2) , memset(vis+1,0,n) , cnt = 0;
    }
}

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    __inline bool merge(int x,int y) {
        return ( x = findfa(x) ) == ( y = findfa(y) ) ? 0 : fa[x] = y;
    }
    __inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

__inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
__inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

__inline void reset() {
    JudgeTree::reset() , DPTree::reset() , ufs.init();
    memset(sel+1,0,m) , memset(su+1,0,m) , fail = 0;
}

int main() {
    static int T;
    T = getint();
    while(T--) {
        n = getint() , m = getint() , reset();
        for(int i=1;i<=m;i++) if( ufs.merge(u[i]=getint(),v[i]=getint()) ) sel[i] = 1 , JudgeTree::addedge(u[i],v[i],i);
        JudgeTree::pre1(1) , JudgeTree::pre2(1);
        for(int i=1;i<=m;i++) if( !sel[i] ) JudgeTree::relink(u[i],v[i]);
        JudgeTree::dfs(1);
        if( fail ) { puts("0"); continue; }
        for(int i=1;i<=m;i++) if( sel[i] && !su[i] ) DPTree::addedge(u[i],v[i]);
        printf("%d\n",DPTree::getans());
    }
    return 0;
}
