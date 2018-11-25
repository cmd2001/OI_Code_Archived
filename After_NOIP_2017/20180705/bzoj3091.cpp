#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=5e4+1e2;

inline lli c2(const int &x) {
    return (lli) x * ( x + 1 );
}
inline lli c3(const int &x) {
    return (lli) x * ( x + 1 ) * ( x + 2 ) / 6;
}
inline lli gcd(lli x,lli y) {
    if( !x || !y ) return x | y;
    register lli t;
    while( ( t = x % y ) ) x = y , y = t;
    return y;
}

struct LinkCutTree {
    int ch[maxn][2],fa[maxn],siz[maxn],rev[maxn];
    lli dat[maxn],su[maxn][2],ls[maxn],ways[maxn],lazy[maxn];

    inline void apply(int pos,const lli &x) {
        if( !pos ) return;
        dat[pos] += x , lazy[pos] += x;
        ways[pos] += x * c3(siz[pos]) , ls[pos] += x * siz[pos];
        su[pos][0] += x * c2(siz[pos]) >> 1 , su[pos][1] += x * c2(siz[pos]) >> 1;
    }
    inline void apply_rev(int pos) {
        if( !pos ) return;
        swap(ch[pos][0],ch[pos][1]) , swap(su[pos][0],su[pos][1]) , rev[pos] ^= 1;
    }
    inline void push(int pos) {
        if( rev[pos] ) apply_rev(ch[pos][0]) , apply_rev(ch[pos][1]) , rev[pos] = 0;
        if( lazy[pos] ) apply(ch[pos][0],lazy[pos]) , apply(ch[pos][1],lazy[pos]) , lazy[pos] = 0;
    }
    inline void maintain(int pos) { // rev[pos] has been used so there is no need to push .
        siz[pos] = 1 , ways[pos] = ls[pos] = su[pos][0] = su[pos][1] = dat[pos];
        if( ch[pos][0] ) {
            ways[pos] += ways[ch[pos][0]] + su[ch[pos][0]][0] * siz[pos] + siz[ch[pos][0]] * su[pos][1];
            su[pos][0] += su[ch[pos][0]][0] + ls[pos] * siz[ch[pos][0]];
            su[pos][1] += su[ch[pos][0]][1] + ls[ch[pos][0]] * siz[pos];
            siz[pos] += siz[ch[pos][0]] , ls[pos] += ls[ch[pos][0]];
        }
        if( ch[pos][1] ) {
            ways[pos] += ways[ch[pos][1]] + su[pos][0] * siz[ch[pos][1]] + siz[pos] * su[ch[pos][1]][1];
            su[pos][0] += su[ch[pos][1]][0] + siz[pos] * ls[ch[pos][1]];
            su[pos][1] += su[ch[pos][1]][1] + ls[pos] * siz[ch[pos][1]];
            siz[pos] += siz[ch[pos][1]] , ls[pos] += ls[ch[pos][1]];
        }
    }
    inline bool isroot(int pos) {
        return pos != ch[fa[pos]][0] && pos != ch[fa[pos]][1];
    }
    inline int gid(int pos) {
        return pos == ch[fa[pos]][1];
    }
    inline void pushchain(int pos) {
        if( !isroot(pos) ) pushchain(fa[pos]);
        push(pos);
    }
    inline void rotate(int x) {
        const int id = gid(x) , f = fa[x];
        fa[x] = fa[f];
        if( !isroot(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        maintain(f) , maintain(x);
    }
    inline void splay(int x) {
        pushchain(x);
        while( !isroot(x) ) {
            if( !isroot(fa[x]) ) rotate(gid(fa[x])==gid(x)?fa[x]:x);
            rotate(x);
        }
    }
    inline void access(int x) {
        int lst = 0;
        while(x) {
            splay(x) , ch[x][1] = lst , maintain(x);
            lst = x , x = fa[x];
        }
    }
    inline void makeroot(int x) {
        access(x) , splay(x) , apply_rev(x);
    }
    inline int findfa(int x) {
        access(x) , splay(x);
        while( ch[x][0] ) x = ch[x][0];
        return x;
    }
    inline void cut(int x,int y) {
        makeroot(x) , access(y) , splay(y);
        if( ch[y][0] == x && siz[y] == 2 ) fa[x] = ch[y][0] = 0 , maintain(y);
    }
    inline void link(int x,int y) {
        if( findfa(x) == findfa(y) ) return;
        makeroot(x) , fa[x] = y;
    }
    inline void update(int x,int y,int v) {
        if( findfa(x) != findfa(y) ) return;
        makeroot(x) , access(y) , splay(y) , apply(y,v);
    }
    inline void query(int x,int y,lli &a,lli &b) {
        static lli g;
        makeroot(x) , access(y) , splay(y);
        g = gcd(a=ways[y],b=c2(siz[y])>>1) , a /= g , b /= g;
    }
    inline void init(int pos,const lli &v) {
        siz[pos] = 1 , ways[pos] = ls[pos] = su[pos][0] = su[pos][1] = dat[pos] = v;
    }
}lct;

int main() {
    static int n,m;
    static lli a,b;
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;i++) scanf("%d",&x) , lct.init(i,x);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , lct.link(a,b);
    for(int i=1,o,u,v,t;i<=m;i++) {
        scanf("%d%d%d",&o,&u,&v);
        if( o == 1 ) lct.cut(u,v);
        else if( o == 2 ) lct.link(u,v);
        else if( o == 3 ) scanf("%d",&t) , lct.update(u,v,t);
        else if( o == 4 ) lct.findfa(u) == lct.findfa(v) ? lct.query(u,v,a,b) , printf("%lld/%lld\n",a,b) : puts("-1");
    }
    return 0;
}

