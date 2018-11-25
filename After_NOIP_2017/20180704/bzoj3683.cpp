#include<cstdio>
#include<cctype>
typedef long long int lli;
typedef long double ldb;
const int maxn=3e5+1e2;

int n;

struct SegmentTree {
    lli lazy[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void push(int pos) {
        if( lazy[pos] ) lazy[lson(pos)] += lazy[pos] , lazy[rson(pos)] += lazy[pos] , lazy[pos] = 0;
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const lli &x) {
        if( ll <= l && r <= rr ) return void(lazy[pos] += x);
        const int mid = ( l + r ) >> 1; push(pos);
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr,x);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,x);
    }
    inline lli query(int pos,int l,int r,const int &tar) {
        if( l == r ) return lazy[pos];
        const int mid = ( l + r ) >> 1; push(pos);
        return tar <= mid ? query(lson(pos),l,mid,tar) : query(rson(pos),mid+1,r,tar);
    }
}cha,sbt;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn];
    int delta[maxn],dfn[maxn],rit[maxn],dd;
    lli c2[maxn],mem[maxn]; // mem means memed ans .
    inline void addedge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void pre(int pos) { // included current point .
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pre(t[at]) , c2[pos] += (lli) siz[pos] * siz[t[at]];
            son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos] ,  siz[pos] += siz[t[at]];
        }
        delta[pos] = siz[pos] - siz[son[pos]];
    }
    inline void dfs(int pos) {
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos , dfn[pos] = ++dd;
        if( son[pos] ) dfs(son[pos]);
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != son[pos] ) dfs(t[at]);
        rit[pos] = dd;
    }
    inline void solve_chain(int pos,const lli &x) { // update pos and fa with val x.
        mem[fa[pos]] += x * ( siz[fa[pos]] - siz[pos] ) , pos = fa[pos];
        while(pos) {
            if( pos != top[pos] ) cha.update(1,1,n,dfn[top[pos]],dfn[pos]-1,x);
            pos = top[pos] , mem[fa[pos]] += x * ( siz[fa[pos]] - siz[pos] ) , pos = fa[pos];
        }
    }
    inline void update_subtree(int pos,const lli &x) {
        sbt.update(1,1,n,dfn[pos],rit[pos],x);
        solve_chain(pos,x*siz[pos]);
    }
    inline void update_point(int pos,const lli &x) {
        mem[pos] += x * ( siz[pos] - 1 );
        solve_chain(pos,x);
    }
    inline ldb query(int pos) {
        const lli ways = c2[pos];
        const lli su = mem[pos] + 2 * sbt.query(1,1,n,dfn[pos]) * c2[pos] + cha.query(1,1,n,dfn[pos]) * delta[pos];
        return (ldb) su / ways;
    }
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , fix = 1; char ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}
inline void getstr(char* s) {
    char ch;
    while( !isalpha(ch=nextchar()) ) ;
    do *s++ = ch; while( isalpha(ch=nextchar()) );
}

int main() {
    static int m;
    static char o[10];
    n = getint() , m = getint();
    for(int i=2;i<=n;i++) Tree::addedge(getint(),i);
    Tree::pre(1) , Tree::dfs(1);
    for(int i=1;i<=n;i++) Tree::update_point(i,getint());
    for(int i=1,p;i<=m;i++) {
        getstr(o) , p = getint();
        if( *o == 'Q' ) printf("%0.6Lf\n",Tree::query(p));
        else if( *o == 'S' ) Tree::update_point(p,getint());
        else if( *o == 'M' ) Tree::update_subtree(p,getint());
    }
    return 0;
}
