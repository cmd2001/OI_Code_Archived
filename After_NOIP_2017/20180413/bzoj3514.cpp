#include<cstdio>
#include<algorithm>
const int maxn=4e5+1e2,maxe=1e7+1e2;
const int inf=0x3f3f3f3f;

struct LinkCutTree {
    int ch[maxn][2],fa[maxn],rev[maxn],dat[maxn],miv[maxn];
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
        miv[pos] = dat[pos];
        if( ch[pos][0] ) miv[pos] = std::min( miv[pos] , miv[ch[pos][0]] );
        if( ch[pos][1] ) miv[pos] = std::min( miv[pos] , miv[ch[pos][1]] );
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
    inline int findfa(int x) {
        access(x) , splay(x);
        while( ch[x][0] ) x = ch[x][0];
        return x;
    }
    inline int query(int x,int y) {
        if( x == y ) return dat[x];
        makeroot(x) , access(y) , splay(y);
        return miv[y];
    }
    inline void init(int n,int m) {
        for(int i=1;i<=n;i++) dat[i] = miv[i] = inf;
        for(int i=1;i<=m;i++) dat[i+n] = miv[i+n] = i;
    }
}lct;

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int& pos,int pre,int l,int r,const int &tar) {
        sum[pos=++cnt] = sum[pre] + 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || rr < l || r < ll ) return 0;
        if( ll <= l && r <= rr ) return sum[pos];
        const int mid = ( l + r ) >> 1;
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
}pst;

int u[maxn>>1],v[maxn>>1],ntr[maxn>>1],root[maxn>>1];

int main() {
    static int n,m,q,tpe,lastans;
    scanf("%d%d%d%d",&n,&m,&q,&tpe) , lct.init(n,m);
    for(int i=1;i<=m;i++) scanf("%d%d",u+i,v+i);
    for(int i=1;i<=m;i++) {
        if( u[i] == v[i] ) ntr[i] = i;
        else {
            if( lct.findfa(u[i]) == lct.findfa(v[i]) ) {
                int t = lct.query(u[i],v[i]); ntr[i] = t;
                lct.cut(u[i],t+n) , lct.cut(v[i],t+n);
            }
            lct.link(u[i],i+n) , lct.link(v[i],i+n);
        }
    }
    for(int i=1;i<=m;i++) pst.insert(root[i],root[i-1],0,m,ntr[i]);
    for(int i=1,l,r;i<=q;i++) {
        scanf("%d%d",&l,&r);
        if( tpe ) l ^= lastans , r ^= lastans;
        lastans = n - ( pst.query(root[r],0,m,0,l-1) - pst.query(root[l-1],0,m,0,l-1) );
        printf("%d\n",lastans);
    }
    return 0;
}
