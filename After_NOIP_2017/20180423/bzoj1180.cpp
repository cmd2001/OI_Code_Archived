#include<cstdio>
#include<algorithm>
const int maxn=3e4+1e2;
 
struct LinkCutTree {
    int ch[maxn][2],fa[maxn],rev[maxn],dat[maxn],sum[maxn];
    inline void apply(int pos) {
        if( pos ) std::swap(ch[pos][0],ch[pos][1]) , rev[pos] ^= 1;
    }
    inline void upgrade(int pos) {
        sum[pos] = dat[pos];
        if( ch[pos][0] ) sum[pos] += sum[ch[pos][0]];
        if( ch[pos][1] ) sum[pos] += sum[ch[pos][1]];
    }
    inline void push(int pos) {
        if( rev[pos] ) apply(ch[pos][0]) , apply(ch[pos][1]) , rev[pos] = 0;
    }
    inline bool isroot(int pos) {
        return pos != ch[fa[pos]][0] && pos != ch[fa[pos]][1];
    }
    inline int gid(int pos) {
        return pos == ch[fa[pos]][1];
    }
    inline void rotate(int x) {
        push(fa[x]) , push(x);
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isroot(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        fa[f] = x , ch[x][id^1] = f;
        upgrade(f) , upgrade(x);
    }
    inline void pushchain(int x) {
        if( !isroot(x) ) pushchain(fa[x]);
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
        int t = 0;
        while(x) {
            splay(x) , ch[x][1] = t , upgrade(x);
            t = x , x = fa[x];
        }
    }
    inline void makeroot(int x) {
        access(x) , splay(x) , apply(x);
    }
    inline void link(int x,int y) {
        makeroot(x) , access(y) , splay(y) , fa[x] = y;
    }
    inline int findfa(int x) {
        access(x) , splay(x);
        while( ch[x][0] ) x = ch[x][0];
        return x;
    }
    inline void update(int x,int v) {
        splay(x) , dat[x] = v , upgrade(x);
    }
    inline int chain(int x,int y) {
        makeroot(x) , access(y) , splay(y);
        return sum[y];
    }
}lct;
 
int main() {
    static int n,m;
    static char o[20];
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",lct.dat+i) , lct.sum[i] = lct.dat[i];
    scanf("%d",&m);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%s%d%d",o,&a,&b);
        if( *o == 'e' ) {
            if( lct.findfa(a) != lct.findfa(b) ) puts("impossible");
            else printf("%d\n",lct.chain(a,b));
        }
        else if( *o == 'b' ) {
            if( lct.findfa(a) == lct.findfa(b) ) puts("no");
            else puts("yes") , lct.link(a,b);
        } else if( *o == 'p' ) lct.update(a,b);
    }
    return 0;
}

