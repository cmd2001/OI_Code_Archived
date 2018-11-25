#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
typedef unsigned long long int ulli;
const int maxn=2e5+1e2,maxe=2e7+1e2,lim=2e5+1;

ulli h[maxn],su[maxn];
bool vis[maxn];

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],cnt;
    ulli dat[maxe];
    inline void insert(int &pos,int pre,int l,int r,const int &tar) {
        dat[pos=++cnt] = dat[pre] ^ h[tar];
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];
    }
    inline ulli getlson(int aa,int ab,int sa,int sb) {
        return dat[lson[aa]] ^ dat[lson[ab]] ^ dat[lson[sa]] ^ dat[lson[sb]];
    }
    inline int query(int aa,int ab,int sa,int sb,int l,int r) { // pos diffs .
        if( l == r ) return l;
        const int mid = ( l + r ) >> 1;
        const ulli sl = getlson(aa,ab,sa,sb);
        if( sl == ( su[mid] ^ su[l-1] ) ) return query(rson[aa],rson[ab],rson[sa],rson[sb],mid+1,r);
        else return query(lson[aa],lson[ab],lson[sa],lson[sb],l,mid);
    }
    inline void reset() {
        ++cnt , memset(lson,0,cnt<<2) , memset(rson,0,cnt<<2) , memset(dat,0,cnt<<3) , cnt = 0;
    }
}pst;

int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn];
int in[maxn],root[maxn];

inline void coredge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline void pre(int pos) {
    siz[pos] = 1 , pst.insert(root[pos],root[fa[pos]],1,lim,in[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}

inline int query(int x,int y) {
    int lc = lca(x,y);
    return pst.query(root[x],root[y],root[lc],root[fa[lc]],1,lim);
}

inline void init() {
    for(int i=1;i<=lim;i++) su[i] = su[i-1] ^ ( h[i] = rand() * rand() * rand() * rand() );
}
inline void reset(int n) {
    pst.reset() , memset(s+1,0,n<<2) , memset(siz+1,0,n<<2) , memset(son+1,0,n<<2) , cnt = 0;
}

namespace FastIO {
    inline char nextchar() {
        static const int BS = 1 << 22;
        static char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? 0 : *st++;
    }
    inline int getint() {
        int ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using FastIO::getint;

int main() {
    static int T,n,m;
    T = getint() , init();
    while(T--) {
        reset(n=getint()) , m = getint();
        for(int i=1;i<=n;i++) in[i] = getint();
        for(int i=1;i<n;i++) addedge(getint(),getint());
        pre(1) , dfs(1);
        for(int i=1;i<=m;i++) printf("%d\n",query(getint(),getint()));
    }
    return 0;
}
