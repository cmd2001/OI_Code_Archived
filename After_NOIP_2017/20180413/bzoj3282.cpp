#include<cstdio>
#include<algorithm>
const int maxn=3e5+1e2;

struct LinkCutTree {
    int ch[maxn][2],fa[maxn],rev[maxn],dat[maxn],sum[maxn];
    inline void apply(int pos) {
        if( !pos ) return;
        std::swap(ch[pos][0],ch[pos][1]) , rev[pos] ^= 1;
    }
    inline void push(int pos) {
        if( rev[pos] ) {
            apply(ch[pos][0]) , apply(ch[pos][1]);
            rev[pos] = 0;
        }
    }
    inline void upgrade(int pos) {
        sum[pos] = dat[pos];
        if( ch[pos][0] ) sum[pos] ^= sum[ch[pos][0]];
        if( ch[pos][1] ) sum[pos] ^= sum[ch[pos][1]];
    }
    inline bool isroot(int x ) {
        return x != ch[fa[x]][0] && x != ch[fa[x]][1];
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        push(fa[x]) , push(x);
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isroot(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        upgrade(f) , upgrade(x);
    }
    inline void pushchain(int pos) {
        if( !isroot(pos) ) pushchain(fa[pos]);
        push(pos);
    }
    inline void splay(int x) {
        pushchain(x);
        while( !isroot(x) ) {
            if( !isroot(fa[x]) ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline void access(int x) {
        int t = 0;
        while(x) {
            splay(x) , ch[x][1] = t , upgrade(x);
            t = x , x = fa[x];
        }
    }
    inline void makeroot(int x) {
        access(x) , splay(x) , apply(x);
    }
    inline void link(int x,int y) { // assert x != y .
        makeroot(x) , makeroot(y) , fa[x] = y;
    }
    inline void cut(int x,int y) { // assert x != y .
        makeroot(x) , access(y) , splay(y);
        if( ch[y][0] == x ) fa[x] = ch[y][0] = 0 , upgrade(y);
    }
    inline void modify(int x,int nv) {
        access(x) , splay(x) , dat[x] = nv , upgrade(x);
    }
    inline int findfa(int x) {
        access(x) , splay(x);
        while( ch[x][0] ) x = ch[x][0];
        return x;
    }
    inline int query(int x,int y) {
        if( x == y ) return dat[x];
        makeroot(x) , access(y) , splay(y);
        return sum[y];
    }
}lct;

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , lct.modify(i,t);
    for(int i=1,o,x,y;i<=m;i++) {
        scanf("%d%d%d",&o,&x,&y);
        if( o == 0 ) printf("%d\n",lct.query(x,y));
        else if( o == 1 ) {
            if( lct.findfa(x) != lct.findfa(y) ) lct.link(x,y);
        } else if( o == 2 ) {
            if( lct.findfa(x) == lct.findfa(y) ) lct.cut(x,y);
        } else if( o == 3 ) lct.modify(x,y);
    }
    return 0;
}
