#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define lli long long int
const int maxn=1e5+1e2;
const int mod=1e9+7;

int cmp;
struct KDTree { // assert root = 1 .
    struct Point {
        int d[2],col,id;
        friend bool operator < (const Point &a,const Point &b) {
            return a.d[cmp] < b.d[cmp];
        }
        friend bool operator == (const Point &a,const Point &b) {
            return a.d[0] == b.d[0] && a.d[1] == b.d[1];
        }
    }ps[maxn],nv[maxn];
    int lson[maxn],rson[maxn],fa[maxn],mi[maxn][2],mx[maxn][2],lazy[maxn],cnt;
    int cov[maxn];
    
    inline void fill(int pos,const Point &p) {
        nv[pos] = p , cov[p.id] = pos;
        for(int i=0;i<2;i++) mi[pos][i] = mx[pos][i] = p.d[i];
    }
    inline void upgrade(int f,int s) {
        if( !s ) return;
        for(int i=0;i<2;i++)
            mi[f][i] = std::min( mi[f][i] , mi[s][i] ) ,
            mx[f][i] = std::max( mx[f][i] , mx[s][i] ) ;
    }
    inline void build(int pos,int dir,int ll,int rr) {
        cmp = dir;
        const int mid = ( ll + rr ) >> 1;
        std::nth_element(ps+ll,ps+mid,ps+rr+1);
        fill(pos,ps[mid]);
        if( ll < mid ) build(lson[pos]=++cnt,dir^1,ll,mid-1) , fa[lson[pos]] = pos;
        if( mid < rr ) build(rson[pos]=++cnt,dir^1,mid+1,rr) , fa[rson[pos]] = pos;
        upgrade(pos,lson[pos]) , upgrade(pos,rson[pos]);
    }
    inline void set(int pos,const int &col) {
        if( !pos ) return;
        lazy[pos] = nv[pos].col = col;
    }
    inline void push(int pos) {
        if( ~lazy[pos] ) {
            set(lson[pos],lazy[pos]) , set(rson[pos],lazy[pos]) ,
            lazy[pos] = -1;
        }
    }
    inline bool in(int pos,const int &sx,const int &tx,const int &sy,const int &ty) {
        return sx <= mi[pos][0] && mx[pos][0] <= tx && sy <= mi[pos][1] && mx[pos][1] <= ty;
    }
    inline bool in(const Point &p,const int &sx,const int &tx,const int &sy,const int &ty) {
        return sx <= p.d[0] && p.d[0] <= tx && sy <= p.d[1] && p.d[1] <= ty;
    }
    inline bool out(int pos,const int &sx,const int &tx,const int &sy,const int &ty) {
        return mx[pos][0] < sx || tx < mi[pos][0] || mx[pos][1] < sy || ty < mi[pos][1];
    }
    inline void update(int pos,const int &sx,const int &tx,const int &sy,const int &ty,const int &x) {
        if( out(pos,sx,tx,sy,ty) ) return;
        if( in(pos,sx,tx,sy,ty) ) {
            return set(pos,x);
        }
        if( in(nv[pos],sx,tx,sy,ty) ) nv[pos].col = x;
        push(pos);
        update(lson[pos],sx,tx,sy,ty,x) , update(rson[pos],sx,tx,sy,ty,x);
    }
    inline void chain(int pos) {
        if( fa[pos] ) chain(fa[pos]);
        push(pos);
    }
    inline int query(int pos) {
        chain(pos);
        return nv[pos].col;
    }
    inline void reset() {
        for(int i=0;i<=cnt;i++) fa[i] = lson[i] = rson[i] = 0 , lazy[i] = -1;
        cnt = 1;
    }
    KDTree() { memset(lazy,-1,sizeof(lazy)); }
}kdt;

int dfn[maxn],dep[maxn],rit[maxn];
int n;

namespace Graph {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt,dd;
    inline void addedge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos) {
        rit[pos] = dfn[pos] = ++dd;
        for(int at=s[pos];at;at=nxt[at]) {
                dep[t[at]] = dep[pos] + 1;
                dfs(t[at]) , rit[pos] = rit[t[at]];
            }
    }
    inline void reset() {
        memset(s,0,sizeof(s)) ,
        cnt = dd = 0;
    }
}

inline void init() {
    Graph::dfs(1);
    for(int i=1;i<=n;i++) kdt.ps[i] = (KDTree::Point){dfn[i],dep[i],1,i};
    kdt.build(1,0,1,n);
}
inline void update(int x,int d,int c) {
    kdt.update(1,dfn[x],rit[x],dep[x]-d,dep[x]+d,c);
}
inline int query(int pos) {
    return kdt.query(kdt.cov[pos]);
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int T,q;
    static lli ans;
    T = getint();
    while(T--) {
        kdt.reset() , Graph::reset() , ans = 0;
        n = getint() , getint() , q = getint();
        for(int i=2,x;i<=n;i++) {
            x = getint();
            Graph::addedge(x,i);
        }
        init();
        for(int i=1,a,l,c;i<=q;i++) {
            a = getint() , l = getint() , c = getint();
            if( c ) update(a,l,c);
            else {
                ans += (lli) i  * query(a) % mod;
                ans %= mod;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}


