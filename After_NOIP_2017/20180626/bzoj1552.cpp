#include<cstdio>
#include<algorithm>
#include<cctype>
typedef unsigned int uint;
typedef unsigned char uchar;
const uint maxn=1e5+1e2;

uint n;
struct pii{uint l,r;};
inline pii mp(const uint &l,const uint &r) { return (pii){l,r}; }

uint root;
struct RotatelessTreap {
    uint lson[maxn],rson[maxn],fa[maxn],siz[maxn],rev[maxn],fix[maxn];
    
    inline void apply(uint pos) {
        if( !pos ) return;
        std::swap(lson[pos],rson[pos]) , rev[pos] ^= 1;
    }
    inline void maintain(uint pos) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
        if(lson[pos]) fa[lson[pos]] = pos;
        if(rson[pos]) fa[rson[pos]] = pos;
    }
    inline void push(uint pos) {
        if( rev[pos] ) apply(lson[pos]) , apply(rson[pos]) , rev[pos] ^= 1;
    }
    inline pii split(uint pos,uint ts) { // left siz is ts .
        if( !pos ) return mp(0,0);
        push(pos);
        if( ts <= siz[lson[pos]] ) {
            pii spl = split(lson[pos],ts);
            lson[pos] = spl.r , maintain(pos);
            return mp(spl.l,pos);
        } else {
            pii spr = split(rson[pos],ts-siz[lson[pos]]-1);
            rson[pos] = spr.l , maintain(pos);
            return mp(pos,spr.r);
        }
    }
    inline uint merge(uint x,uint y) { // assert x on left .
        if( !x || !y ) return x | y;
        if( fix[x] > fix[y] ) { // great root heap .
            push(x) , rson[x] = merge(rson[x],y) , maintain(x);
            return x;
        } else {
            push(y) , lson[y] = merge(x,lson[y]) , maintain(y);
            return y;
        }
    }
    inline void pushchain(uint pos) {
        if( fa[pos] ) pushchain(fa[pos]);
        push(pos);
    }
    inline uint getrnk(uint pos) {
        pushchain(pos);
        uint ret = siz[lson[pos]] + 1;
        while(pos) {
            if( pos == rson[fa[pos]] ) ret += siz[lson[fa[pos]]] + 1;
            pos = fa[pos];
        }
        return ret;
    }
    inline void init() {
        for(uint i=1;i<maxn;i++) fix[i] = i , siz[i] = 1;
        std::random_shuffle(fix+1,fix+maxn);
    }
}treap;

struct Node {
    uint h,id;
    friend bool operator < (const Node &a,const Node &b) {
        return a.h != b.h ? a.h < b.h : a.id < b.id;
    }
}in[maxn];

inline uchar nextchar() {
    static const uint BS = 1 << 21;
    static uchar buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? 0 : *st++;
}
inline uint getint() {
    uint ret = 0;
    uchar ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , treap.init();
    for(uint i=1;i<=n;i++) in[i].h = getint() , in[i].id = i , root = treap.merge(root,i);
    std::sort(in+1,in+1+n);
    for(uint i=1;i<=n;i++) {
        uint l = i , r = treap.getrnk(in[i].id); printf("%d%c",r,i!=n?' ':'\n');
        pii spl = treap.split(root,l-1) , spr = treap.split(spl.r,r-l+1);
        treap.apply(spr.l) , root = treap.merge(spl.l,treap.merge(spr.l,spr.r));
    }
    return 0;
}

