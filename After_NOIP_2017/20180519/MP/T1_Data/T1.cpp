#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cctype>
#define debug cout
using namespace std;
typedef unsigned int uint;
const int maxn=7e5+1e2;

struct pii{uint l,r;};

uint in[maxn],roots[maxn<<1],cnt;
std::unordered_map<uint,uint> cov;

struct RotatelessTreap {
    int lson[maxn],rson[maxn],siz[maxn],fix[maxn];
    
    inline void maintain(const uint &pos) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
    }
    inline pii split(uint pos,const uint &id) { // left is <= id .
        if( !pos ) return (pii){0u,0u};
        if( id < pos ) { // split pos into right .
            pii spl = split(lson[pos],id);
            lson[pos] = spl.r , maintain(pos);
            return (pii){spl.l,pos};
        } else { // split pos into left .
            pii spr = split(rson[pos],id);
            rson[pos] = spr.l , maintain(pos);
            return (pii){pos,spr.r};
        }
    }
    inline uint merge(uint x,uint y) {
        if( !x || !y ) return x | y;
        if( x > y ) std::swap(x,y);
        if( fix[x] > fix[y] ) { // big root heap .
            rson[x] = merge(rson[x],y);
            return maintain(x) , x;
        } else {
            lson[y] = merge(lson[y],x);
            return maintain(y) , y;
        }
    }
    inline uint query(uint &root,uint l,uint r) { // return size of segment[l,r] .
        pii spl = split(root,l-1) , spr = split(spl.r,r);
        const uint ll = spl.l , mid = spr.l , rr = spr.r , ret = siz[mid];
        root = merge(ll,merge(mid,rr));
        return ret;
    }
    inline void modify(uint pos,uint &ort,uint &nrt) {
        pii spl , spr;
        spl = split(ort,pos-1) , spr = split(spl.r,pos) , ort = merge(spl.l,spr.r);
        spl = split(nrt,pos) , nrt = merge(spl.l,merge(pos,spl.r));
    }
    inline void init(uint n) {
        for(uint i=1;i<=n;i++) fix[i] = i , siz[i] = 1;
        std::random_shuffle(fix+1,fix+1+n);
    }
}treap;

namespace FastIO { // fastoutput may be uselsss .
    const uint BS = 1 << 20;
    unsigned char ibuf[BS],*st,*ed;
    
    inline unsigned char nextchar() {
        if( st == ed ) ed = ibuf + fread(st=ibuf,1,BS,stdin);
        return st == ed ? 0 : *st++;
    }
    inline uint getint() {
        uint ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using namespace FastIO;


inline void initer() { // it can work 
    static const char seed[] = "KurenaiKisaragi";
    uint su = 0 , li = strlen(seed);
    for(uint i=0;i<li;i++) su += seed[i];
    srand(su);
}

int main() {
    static uint n,m,lastans;
    initer() , treap.init(n=getint()) , m = getint();
    for(uint i=1;i<=n;i++) {
        if( cov.find(in[i]=getint()) == cov.end() ) cov[in[i]] = ++cnt;
        roots[cov[in[i]]] = treap.merge(roots[cov[in[i]]],i);
    }
    for(uint i=1,l,r,k,p,x;i<=m;i++) {
        if( getint() == 1 ) {
            l = ( getint() + lastans ) % n + 1 , r = ( getint() + lastans ) % n + 1 , k = getint();
            if( l > r ) std::swap(l,r);
            if( cov.find(k) == cov.end() ) puts("0") , lastans = 0;
            else printf("%u\n",lastans=treap.query(roots[cov[k]],l,r));
        } else {
            p = ( getint() + lastans ) % n + 1;
            if( cov.find(x=getint()) == cov.end() ) cov[x] = ++cnt;
            treap.modify(p,roots[cov[in[p]]],roots[cov[x]]) , in[p] = x;
        }
    }
    return 0;
}
