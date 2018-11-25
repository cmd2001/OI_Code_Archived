#include<cstdio>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=3e5+1e2,maxl=19;

int in[maxn],rec[maxn];
struct SegmentTree {
    lli su[maxn<<2],lazy[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void apply(const int &pos,const int &l,const int &r,const lli &x) {
        su[pos] += ( r - l + 1 ) * x , lazy[pos] += x;
    }
    inline void push(const int &pos,const int &l,const int &mid,const int &r) {
        if( lazy[pos] ) apply(lson(pos),l,mid,lazy[pos]) , apply(rson(pos),mid+1,r,lazy[pos]) , lazy[pos] = 0;
    }
    inline void maintain(int pos) {
        su[pos] = su[lson(pos)] + su[rson(pos)];
    }
    inline void build(int pos,int l,int r) {
        if( l == r ) return void( su[pos] = rec[l] );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , maintain(pos);
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const lli &x) {
        if( ll <= l && r <= rr ) return apply(pos,l,r,x);
        const int mid = ( l + r ) >> 1; push(pos,l,mid,r);
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr,x);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,x);
        maintain(pos);
    }
    inline lli query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return su[pos];
        const int mid = ( l + r ) >> 1; push(pos,l,mid,r);
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return query(lson(pos),l,mid,ll,rr) + query(rson(pos),mid+1,r,ll,rr);
    }
}sgt;

int n,root;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int dfn[maxn],rit[maxn],dep[maxn],anc[maxn][maxl];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void dfs(int pos) {
        static int dd;
        rec[dfn[pos]=++dd] = in[pos] , dep[pos] = dep[*anc[pos]] + 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != *anc[pos] ) *anc[t[at]] = pos , dfs(t[at]);
        rit[pos] = dd;
    }
    inline void init() {
        for(int j=1;j<maxl;j++) for(int i=1;i<=n;i++) anc[i][j] = anc[anc[i][j-1]][j-1];
    }
    inline bool insideSubtree(int pos,int jud) {
        return dfn[pos] <= dfn[jud] && dfn[jud] <= rit[pos];
    }
    inline int coreLCA(int u,int v) {
        if( dep[u] < dep[v] ) std::swap(u,v);
        for(int i=maxl-1;~i;i--) if( dep[u] - ( 1 << i ) >= dep[v] ) u = anc[u][i];
        if( u == v ) return u;
        for(int i=maxl-1;~i;i--) if( anc[u][i] != anc[v][i] ) u = anc[u][i] , v = anc[v][i];
        return *anc[u];
    }
    inline int nearestPoint(int u,int f) {
        for(int i=maxl-1;~i;i--) if( dep[u] - ( 1 << i ) > dep[f] ) u = anc[u][i];
        return u;
    }
    inline int getLCA(int u,int v) {
        int luv = coreLCA(u,v);
        if( !insideSubtree(luv,root) ) return luv;
        int lur = coreLCA(u,root) , lvr = coreLCA(v,root);
        return dep[lur] > dep[lvr] ? lur : lvr;
    }
    inline void updateSubtree(int pos,const lli &x) {
        if( pos == root ) sgt.update(1,1,n,1,n,x);
        else if( !insideSubtree(pos,root) ) sgt.update(1,1,n,dfn[pos],rit[pos],x);
        else {
            const int p = nearestPoint(root,pos);
            sgt.update(1,1,n,1,dfn[p]-1,x);
            if( rit[p] != n) sgt.update(1,1,n,rit[p]+1,n,x);
        }
    }
    inline lli querySubtree(int pos) {
        if( pos == root ) return sgt.query(1,1,n,1,n);
        else if( !insideSubtree(pos,root) ) return sgt.query(1,1,n,dfn[pos],rit[pos]);
        else {
            const int p = nearestPoint(root,pos);
            lli ret = sgt.query(1,1,n,1,dfn[p]-1);
            if( rit[p] != n ) ret += sgt.query(1,1,n,rit[p]+1,n);
            return ret;
        }
    }
}

namespace IO {
    inline char nextchar() {
        static const int BS = 1 << 21;
        static char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? -1 : *st++;
    }
    inline int getint() {
        int ret = 0 , fix = 1;
        char ch;
        while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret * fix;
    }
}
using IO::getint;

int main() {
    static int q;
    n = getint() , q = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    for(int i=1,a,b;i<n;i++) a = getint() , b = getint() , Tree::addedge(a,b);
    Tree::dfs(root=1) , Tree::init() , sgt.build(1,1,n);
    for(int i=1,o,u,v,x;i<=q;i++) {
        o = getint() , u = getint();
        if( o == 1 ) root = u;
        else if( o == 2 ) v = getint() , x = getint() , Tree::updateSubtree(Tree::getLCA(u,v),x);
        else if( o == 3 ) printf("%lld\n",Tree::querySubtree(u));
    }
    return 0;
}
