#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        if( ( x = findfa(x) ) != ( y = findfa(y) ) ) fa[x] = y;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

int u[maxn],v[maxn],col[maxn],deg[maxn],siz[maxn]; // col = 1 means black .
int ans,cnt; // cnt is count if odd degree .

inline void rev(int id) {
    int fa = ufs.findfa(u[id]);
    if( col[id] ) {
        if( !--siz[fa] ) --ans;
        if( 1 & --deg[u[id]]) ++cnt;
        else --cnt;
        if( 1 & --deg[v[id]] ) ++cnt;
        else --cnt;
    } else {
        if( ++siz[fa] == 1 ) ++ans;
        if( 1 & ++deg[u[id]] ) ++cnt;
        else --cnt;
        if( 1 & ++deg[v[id]] ) ++cnt;
        else -- cnt;
    }
    col[id] ^= 1;
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0; char ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int n,m,q;
    ufs.init( n = getint() ) , m = getint();
    for(int i=1;i<=m;i++) {
        ufs.merge(u[i]=getint(),v[i]=getint());
        if( col[i] = getint() ) {
            if( 1 & ++deg[u[i]] ) ++cnt;
            else --cnt;
            if( 1 & ++deg[v[i]] ) ++cnt;
            else --cnt;
        }
    }
    for(int i=1;i<=m;i++) if( col[i] && ++siz[ufs.findfa(u[i])] == 1 ) ++ans;
    q = getint();
    for(int i=1,o;i<=q;i++) {
        if( ( o = getint() ) == 2 ) printf("%d\n",cnt?-1:ans);
        else rev(getint()+1);
    }
    return 0;
}

