#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int n;
struct pii{int l,r;};
inline pii mp(const int &l,const int &r) { return (pii){l,r}; }

int root;
struct RotatelessTreap {
    int lson[maxn],rson[maxn],fa[maxn],siz[maxn],rev[maxn],fix[maxn];
    
    inline void apply(int pos) {
        if( !pos ) return;
        swap(lson[pos],rson[pos]) , rev[pos] ^= 1;
    }
    inline void maintain(int pos) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
        if(lson[pos]) fa[lson[pos]] = pos;
        if(rson[pos]) fa[rson[pos]] = pos;
    }
    inline void push(int pos) {
        if( rev[pos] ) apply(lson[pos]) , apply(rson[pos]) , rev[pos] ^= 1;
    }
    inline pii split(int pos,int ts) { // left siz is ts .
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
    inline int merge(int x,int y) { // assert x on left .
        if( !x || !y ) return x | y;
        if( fix[x] > fix[y] ) { // great root heap .
            push(x) , rson[x] = merge(rson[x],y) , maintain(x);
            return x;
        } else {
            push(y) , lson[y] = merge(x,lson[y]) , maintain(y);
            return y;
        }
    }
    inline void pushchain(int pos) {
        if( fa[pos] ) pushchain(fa[pos]);
        push(pos);
    }
    inline int getrnk(int pos) {
        pushchain(pos);
        int ret = siz[lson[pos]] + 1;
        while(pos) {
            if( pos == rson[fa[pos]] ) ret += siz[lson[fa[pos]]] + 1;
            pos = fa[pos];
        }
        return ret;
    }
    inline void init() {
        for(int i=1;i<maxn;i++) fix[i] = i , siz[i] = 1;
        random_shuffle(fix+1,fix+maxn);
    }
}treap;

struct Node {
    int h,id;
    friend bool operator < (const Node &a,const Node &b) {
        return a.h != b.h ? a.h < b.h : a.id < b.id;
    }
}in[maxn];

int main() {
    scanf("%d",&n) , treap.init();
    for(int i=1;i<=n;i++) scanf("%d",&in[i].h) , in[i].id = i , root = treap.merge(root,i);
    sort(in+1,in+1+n);
    for(int i=1;i<=n;i++) {
        int l = i , r = treap.getrnk(in[i].id); printf("%d%c",r,i!=n?' ':'\n');
        pii spl = treap.split(root,l-1) , spr = treap.split(spl.r,r-l+1);
        treap.apply(spr.l) , root = treap.merge(spl.l,treap.merge(spr.l,spr.r));
    }
    return 0;
}

