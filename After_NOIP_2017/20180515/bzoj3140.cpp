#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define bool unsigned char
const unsigned maxn=6e3+1e2;
const unsigned inf=0x3f3f3f3f;

unsigned x[maxn],y[maxn],z[maxn];
unsigned a,b,c,siz,ans,full;

unsigned fa[maxn];
bool e[maxn][maxn],vis[maxn];

inline bool dfs(unsigned pos) {
    for(unsigned t=1;t<=c;t++) if( e[pos][t] && !vis[t] ) {
        vis[t] = 1;
        if( !fa[t] || dfs(fa[t]) ) return fa[t] = pos , 1;
    }
    return 0;
}
inline void pir(unsigned &ret) { // mx is b + c .
    memset(fa+1,0,c<<2);
    for(unsigned i=1;i<=b;i++) {
        memset(vis+1,0,c) , ret += dfs(i);
        if( ret >= ans ) return;
    }
}
inline void reset() {
    for(unsigned i=1;i<=b;i++) for(unsigned j=1;j<=c;j++) e[i][j] = 0;
}
inline unsigned calc(unsigned sta) { // sta is selected .
    unsigned ret = __builtin_popcount(sta);
    if( ret >= ans ) return ret;
    reset();
    for(unsigned i=siz;i;i--) if( ! ( sta & ( 1u << ( x[i] - 1 ) ) ) ) e[y[i]][z[i]] = 1;
    return pir(ret) , ret;
}

inline char nextchar() {
    static const unsigned BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? 0 : *st++;
}
inline unsigned getint() {
    unsigned ret = 0 , ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static unsigned T;
    T = getint();
    while(T--) {
        a = getint() , b = getint() , c = getint() , siz = 0 , ans = inf;
        for(unsigned i=1;i<=a;i++) for(unsigned j=1;j<=b;j++) for(unsigned k=1;k<=c;k++) if(getint()) x[++siz] = i , y[siz] = j , z[siz] = k;
        if( b > c ) std::swap(y,z) , std::swap(b,c);
        if( a > b ) std::swap(x,y) , std::swap(a,b);
        if( b > c ) std::swap(y,z) , std::swap(b,c);
        full = 1 << a;
        for(unsigned i=0;i<full;i++) ans = std::min( ans , calc(i) );
        printf("%d\n",ans);
    }
    return 0;
}
