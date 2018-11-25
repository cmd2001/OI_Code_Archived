#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstdlib>
const int maxn=8e4+1e2;

//#define debug cout
#ifdef debug
#include<iostream>
#include<cassert>
using namespace std;
#endif

struct pii{int l,r;};
inline pii mp(const int &l,const int &r) { return (pii){l,r}; }

int root;
struct RotatelessTreap {
    int lson[maxn],rson[maxn],fa[maxn],siz[maxn],fix[maxn];
    inline void maintain(int pos) {
        siz[pos] = 1 , fa[pos] = 0;
        if( lson[pos] ) siz[pos] += siz[lson[pos]] , fa[lson[pos]] = pos;
        if( rson[pos] ) siz[pos] += siz[rson[pos]] , fa[rson[pos]] = pos;
    }
    inline pii split(int pos,int ts) { // left siz is ts .
        if( !pos ) return mp(0,0);
        if( ts <= siz[lson[pos]] ) { // split pos to right .
            pii spl = split(lson[pos],ts);
            lson[pos] = spl.r , maintain(pos);
            return mp(spl.l,pos);
        } else {
            pii spr = split(rson[pos],ts-siz[lson[pos]]-1);
            rson[pos] = spr.l , maintain(pos);
            return mp(pos,spr.r);
        }
    }
    inline int merge(int x,int y) {
        if( !x || !y ) return x | y;
        if( fix[x] > fix[y] ) {
            rson[x] = merge(rson[x],y) , maintain(x);
            return x;
        } else {
            lson[y] = merge(x,lson[y]) , maintain(y);
            return y;
        }
    }
    inline int getrnk(int x) {
        int ret = 1 + siz[lson[x]];
        while(x) {
            if(x == rson[fa[x]] ) ret += siz[lson[fa[x]]] + 1;
            x = fa[x];
        }
        return ret;
    }
    inline int kth(int k) {
        int pos = root;
        while(1) {
            if( k == siz[lson[pos]] + 1 ) return pos;
            else if( k <= siz[lson[pos]] ) pos = lson[pos];
            else k -= siz[lson[pos]] + 1 , pos = rson[pos];
        }
    }
    inline void initfix(int n) {
        for(int i=1;i<=n;i++) fix[i] = i , siz[i] = 1;
        std::random_shuffle(fix+1,fix+1+n);
    }
    inline void split_out(int x) {
        int rnk = getrnk(x);
        pii spl = split(root,rnk-1) , spr = split(spl.r,1);
        root = merge(spl.l,spr.r);
    }
    inline void move(int p,int d) {
        if( !d ) return;
        int rnk = getrnk(p);
        pii spl = split(root,rnk-1) , spr = split(spl.r,1);
        if( d == 1 ) { // move right .
            pii spp = split(spr.r,1);
            root = merge(merge(spl.l,spp.l),merge(p,spp.r));
        } else {
            pii spp = split(spl.l,rnk-2);
            root = merge(merge(spp.l,p),merge(spp.r,spr.r));
        }
    }
    #ifdef debug
    inline void dfs(int pos) {
        if( !pos ) return;
        dfs(lson[pos]);
        if(lson[pos]) assert(fa[lson[pos]]==pos);
        debug<<pos<<" ";
        dfs(rson[pos]);
        if(rson[pos]) assert(fa[rson[pos]]==pos);
        assert(siz[pos]==siz[lson[pos]]+siz[rson[pos]]+1);
    }
    #endif
}treap;

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
    static int n,m;
    static char o[25];
    treap.initfix( n = getint() ) , m = getint();
    for(int i=1;i<=n;i++) root = treap.merge(root,getint());
    for(int i=1,p,x;i<=m;i++) {
        getstr(o) , p = getint();
        if( *o == 'Q' ) printf("%d\n",treap.kth(p));
        else if( *o == 'T' ) treap.split_out(p) , root = treap.merge(p,root);
        else if( *o == 'B' ) treap.split_out(p) , root = treap.merge(root,p);
        else if( *o == 'A' ) printf("%d\n",treap.getrnk(p)-1);
        else x = getint() , treap.move(p,x);
    }
    return 0;
}
