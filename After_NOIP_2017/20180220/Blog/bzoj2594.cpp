#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=1e5+1e2,maxm=1e6+1e2,maxp=1.2e6+1e2;
 
int n,m,q;
struct LCT {
    int ch[maxp][2],fa[maxp],v[maxp],mx[maxp],rev[maxp];
     
    inline void applyrev(int pos) {
        if( !pos ) return;
        rev[pos] ^= 1 ,
        std::swap(ch[pos][0],ch[pos][1]);
    }
    inline void update(int pos) {
        mx[pos] = pos;
        if( v[mx[ch[pos][0]]] > v[mx[pos]] ) mx[pos] = mx[ch[pos][0]];
        if( v[mx[ch[pos][1]]] > v[mx[pos]] ) mx[pos] = mx[ch[pos][1]];
    }
    inline void push(int pos) {
        if( !rev[pos] ) return;
        applyrev(ch[pos][0]) ,
        applyrev(ch[pos][1]) ,
        rev[pos] = 0;
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline bool isroot(int x) {
        return x != ch[fa[x]][0] && x != ch[fa[x]][1];
    }
    inline void rotate(int x) {
        push(fa[x]) , push(x);
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isroot(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        update(f) , update(x);
    }
    inline void pushchain(int x) {
        if( fa[x] ) pushchain(fa[x]);
        push(x);
    }
    inline void splay(int x) {
        pushchain(x);
        while( !isroot(x) ) {
            if( !isroot(fa[x]) ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline void access(int x) {
        int y = 0;
        while( x ) {
            splay(x) , ch[x][1] = y , update(x) ,
            y = x , x = fa[x];
        }
    }
    inline void mkroot(int x) {
        access(x) , splay(x) , applyrev(x);
    }
    inline void link(int x,int y) {
        mkroot(x) , fa[x] = y;
    }
    inline void cut(int x,int y) {
        mkroot(x);
        access(y) , splay(y);
        fa[x] = ch[y][0] = 0 , update(y); // now we assert x == ch[y][0] ( it must be true ) .
    }
    inline int query(int x,int y) {
        mkroot(x);
        access(y) , splay(y);
        return mx[y]; // y shouldn't have ch[1] .
    }
}t;
 
struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        if( x != y ) fa[y] = x;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;
 
struct Edge {
    int x,y,w,id,sta;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
}es[maxm];
bool cmp(const Edge &a,const Edge &b) {
    return a.w < b.w;
}
 
int ope[maxn],x[maxn],y[maxn],id[maxn],ans[maxn]; // ope == 1 means modify .
 
inline void getans() {
    for(int i=q;i;i--) {
        if( !ope[i] ) {
            int p = t.query(x[i],y[i]);
            ans[i] = t.v[p];
        } else {
            if( ufs.findfa(x[i]) != ufs.findfa(y[i]) ) {
                ufs.merge(x[i],y[i]);
                t.link(x[i],id[i]+n) , t.link(y[i],id[i]+n);
            } else {
                int p = t.query(x[i],y[i]);
                if( t.v[p] > t.v[id[i]+n] ) {
                    t.cut(x[i],p) , t.cut(y[i],p);
                    t.link(x[i],id[i]+n) , t.link(y[i],id[i]+n);
                }
            }
        }
    }
}
inline void pre() {
    std::sort(es+1,es+1+m,cmp) , ufs.init();
    for(int i=1;i<=m;i++)
        if( !es[i].sta && ufs.findfa(es[i].x) != ufs.findfa(es[i].y) ) {
            ufs.merge(es[i].x,es[i].y);
            t.link(es[i].x,es[i].id+n) , t.link(es[i].y,es[i].id+n);
        }
}
 
inline void init() {
    for(int i=1;i<=m;i++) {
        const int id = i + n;
        t.v[id] = es[i].w , t.mx[id] = id;
    }
    std::sort(es+1,es+1+m);
    for(int i=1;i<=q;i++) 
        if( ope[i] ) {
            int at = std::lower_bound(es+1,es+1+m,(Edge){x[i],y[i],0,0,0}) - es;
            es[at].sta = 1 , id[i] = es[at].id;
        }
}
 
inline char nextchar() {
    const int BS = 1 << 22;
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
 
int main() {
    n = getint() , m = getint() , q = getint();
    for(int i=1;i<=m;i++) {
        es[i].x = getint() , es[i].y = getint() , es[i].w = getint() , es[i].id = i;
        if( es[i].x > es[i].y ) std::swap( es[i].x , es[i].y );
    }
    for(int i=1;i<=q;i++) {
        ope[i] = getint() , x[i] = getint() , y[i] = getint() , --ope[i];
        if( x[i] > y[i] ) std::swap( x[i] , y[i] );
    }
    init() , pre() , getans();
    for(int i=1;i<=q;i++) if( !ope[i] ) printf("%d\n",ans[i]);
    return 0;
}
