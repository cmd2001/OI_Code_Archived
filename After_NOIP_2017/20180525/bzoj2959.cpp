#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=1.5e5+1e2;

int in[maxn],n;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return x == fa[x] ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        if( ( x = findfa(x) ) != ( y = findfa(y) ) ) fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs,lnk;

struct LinkCutTree {
    int ch[maxn][2],fa[maxn],rev[maxn],dat[maxn],su[maxn],stk[maxn],top;
    inline void apply(int pos) {
        if( !pos ) return;
        rev[pos] ^= 1 , std::swap(ch[pos][0],ch[pos][1]);
    }
    inline void push(int pos) {
        if( rev[pos] ) apply(ch[pos][0]) , apply(ch[pos][1]) , rev[pos] = 0;
    }
    inline void maintain(int pos) {
        su[pos] = dat[pos] + su[ch[pos][0]] + su[ch[pos][1]];
    }
    inline bool isroot(int x) {
        return x != ch[fa[x]][0] && x != ch[fa[x]][1];
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isroot(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        maintain(f) , maintain(x);
    }
    inline void splay(int x) {
        stk[++top] = x; // there is no need to findfa(x) again .
        for(int i=x;!isroot(i);i=fa[i]) stk[++top] = fa[i] = ufs.findfa(fa[i]);
        while(top) push(stk[top--]);
        while( !isroot(x) ) {
            if( !isroot(fa[x]) ) rotate(gid(fa[x])==gid(x)?fa[x]:x);
            rotate(x);
        }
    }
    inline void access(int x) {
        int lst = 0;
        while(x) splay(x) , ch[x][1] = lst , maintain(x) , lst = x , x = fa[x] = ufs.findfa(fa[x]);
    }
    inline void makeroot(int x) {
        access(x) , splay(x) , apply(x);
    }
    inline void update(int x,const int &nv) {
        splay(x) , su[x] += nv , dat[x] += nv;
    }
    inline void dfs(int pos,const int &tar) {
        if( pos != tar ) dat[tar] += dat[pos] , ufs.merge(pos,tar);
        push(pos);
        if( ch[pos][0] ) dfs(ch[pos][0],tar);
        if( ch[pos][1] ) dfs(ch[pos][1],tar);
        ch[pos][0] = ch[pos][1] = 0;
    }
    inline void merge(int x,int y) { // merge chain x -> y into x .
        makeroot(x) , access(y) , splay(y);
        dfs(y,y) , ch[y][0] = ch[y][1] = 0 , maintain(y);
    }
    inline void link(int x,int y) {
        makeroot(x) , fa[x] = y;
    }
    inline int query(int x,int y) {
        makeroot(x) , 
        access(y) , splay(y);
        return su[y];
    }
}lct;

namespace FastIO { // fastoutput may be uselsss .
    const int BS = 1 << 22;
    unsigned char ibuf[BS],*st,*ed;
    
    inline char nextchar() {
        if( st == ed ) ed = ibuf + fread(st=ibuf,1,BS,stdin);
        return st == ed ? 0 : *st++;
    }
    inline int getint() {
        int ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using FastIO::getint;

int main() {
    static int m;
    n = getint() , m = getint() , ufs.init() , lnk.init();
    for(int i=1;i<=n;i++) lct.su[i] = lct.dat[i] = in[i] = getint();
    for(int i=1,o,a,b;i<=m;i++) {
        o = getint() , a = getint() , b = getint();
        if( o == 1 ) {
            if( lnk.findfa(a) != lnk.findfa(b) ) lnk.merge(a,b) , lct.link(ufs.findfa(a),ufs.findfa(b));
            else if( ufs.findfa(a) != ufs.findfa(b) ) lct.merge(ufs.findfa(a),ufs.findfa(b));
        } else if( o == 2 ) lct.update(ufs.findfa(a),b-in[a]) , in[a] = b;
        else if( o == 3 ) {
            if( lnk.findfa(a) != lnk.findfa(b) ) puts("-1");
            else printf("%d\n",lct.query(ufs.findfa(a),ufs.findfa(b)));
        }
    }
    return 0;
}

