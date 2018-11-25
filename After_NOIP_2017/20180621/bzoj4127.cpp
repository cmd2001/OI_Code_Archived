#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int in[maxn],rin[maxn],n;

struct SegmentTree {
    lli mi[maxn<<2],smx[maxn<<2],su[maxn<<2],lazy[maxn<<2];
    int sizbel[maxn<<2],sizabo[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void apply(int pos,bool ispoint,const lli &val) {
        lazy[pos] += val , smx[pos] += val;
        if( !ispoint ) mi[pos] += val , su[pos] += ( sizabo[pos] - sizbel[pos] ) * val; // val will not make any change .
        else {
            if( mi[pos] < 0 ) {
                if( mi[pos] + val < 0 ) su[pos] -= val , mi[pos] += val;
                else su[pos] = ( mi[pos] += val ) , sizbel[pos] = 0 , sizabo[pos] = 1 , smx[pos] = -inf;
            } else su[pos] += val;
        }
    }
    inline void push(int pos) {
        if( lazy[pos] ) apply(lson(pos),0,lazy[pos]) , apply(rson(pos),0,lazy[pos]) , lazy[pos] = 0;
    }
    inline void maintain(int pos) {
        mi[pos] = min(mi[lson(pos)],mi[rson(pos)]) , su[pos] = su[lson(pos)] + su[rson(pos)] , smx[pos] = max( smx[lson(pos)] , smx[rson(pos)] );
        sizabo[pos] = sizabo[lson(pos)] + sizabo[rson(pos)] , sizbel[pos] = sizbel[lson(pos)] + sizbel[rson(pos)];
    }
    inline void build(int pos,int l,int r) {
        if( l == r ) {
            mi[pos] = rin[l];
            if( rin[l] >= 0 ) su[pos] = rin[l] , sizabo[pos] = 1 , smx[pos] = -inf;
            else su[pos] = -rin[l] , sizbel[pos] = 1 , smx[pos] = rin[l];
            return;
        } const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , maintain(pos);
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const lli &val) {
        if( rr < l || r < ll ) return;
        //debug<<"pos = "<<pos<<"mi = "<<mi[pos]<<"smx = "<<smx[pos]<<endl;
        if( ( ll <= l && r <= rr ) && ( mi[pos] >= 0 || smx[pos] + val < 0 ) ) return apply(pos,0,val);
        if( l == r ) return apply(pos,1,val);
        const int mid = ( l + r ) >> 1; push(pos); // applying lazy[pos] will not make any change .
        update(lson(pos),l,mid,ll,rr,val) , update(rson(pos),mid+1,r,ll,rr,val) , maintain(pos);
    }
    inline lli query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return su[pos];
        const int mid = ( l + r ) >> 1; push(pos);
        lli ret = 0;
        if( ll <= mid ) ret += query(lson(pos),l,mid,ll,rr);
        if( mid < rr ) ret += query(rson(pos),mid+1,r,ll,rr);
        return ret;
    }
}sgt;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int dep[maxn],siz[maxn],fa[maxn],son[maxn],top[maxn],dfn[maxn];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void pre(int pos) {
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]) , siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
    }
    inline void dfs(int pos) {
        static int dd;
        rin[dfn[pos]=++dd] = in[pos] , top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        if( son[pos] ) dfs(son[pos]);
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
    }
    inline void apply(int x,int y,const lli &val) {
        while( top[x] != top[y] ) {
            if( dep[top[x]] < dep[top[y]] ) swap(x,y);
            sgt.update(1,1,n,dfn[top[x]],dfn[x],val) , x = fa[top[x]];
        }
        if( dfn[x] > dfn[y] ) swap(x,y);
        sgt.update(1,1,n,dfn[x],dfn[y],val);
    }
    inline lli query(int x,int y) {
        lli ret = 0;
        while( top[x] != top[y] ) {
            if( dep[top[x]] < dep[top[y]] ) swap(x,y);
            ret += sgt.query(1,1,n,dfn[top[x]],dfn[x]) , x = fa[top[x]];
        }
        if( dfn[x] > dfn[y] ) swap(x,y);
        return ret += sgt.query(1,1,n,dfn[x],dfn[y]);
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
        int ret = 0 , fix = 1 , ch;
        while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret * fix;
    }
}
using IO::getint;

int main() {
    static int m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    for(int i=1,a,b;i<n;i++) a = getint() , b = getint() , Tree::addedge(a,b);
    Tree::pre(1) , Tree::dfs(1) , sgt.build(1,1,n);
    for(int i=1,o,u,v;i<=m;i++) {
        o = getint() , u = getint() , v = getint();
        if( o == 1 ) Tree::apply(u,v,getint());
        else if( o == 2 ) printf("%lld\n",Tree::query(u,v));
    }
    return 0;  
}

