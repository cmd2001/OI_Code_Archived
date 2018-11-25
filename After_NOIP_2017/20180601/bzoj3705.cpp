#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<cctype>
typedef unsigned int uint;
const uint maxn=2e3+1e2;
const uint basex=13,basey=23;

uint h[4][maxn][maxn],powsx[maxn],powsy[maxn];
int n,m,ans;

inline bool judge(int sx,int sy,int tx,int ty) {
    const uint px = powsx[tx-sx+1] , py = powsy[ty-sy+1];
    uint hsh = h[0][tx][ty] + h[0][sx-1][sy-1] * px * py - h[0][sx-1][ty] * py - h[0][tx][sy-1] * px , tar;
    tar = h[1][tx][sy] + h[1][sx-1][ty+1] * px * py - h[1][sx-1][sy] * py - h[1][tx][ty+1] * px;
    if( hsh != tar ) return 0;
    tar = h[2][sx][ty] + h[2][tx+1][sy-1] * px * py - h[2][tx+1][ty] * py - h[2][sx][sy-1] * px;
    if( hsh != tar ) return 0;
    tar = h[3][sx][sy] + h[3][tx+1][ty+1] * px * py - h[3][tx+1][sy] * py - h[3][sx][ty+1] * px;
    if( hsh != tar ) return 0;
    return 1;
}
inline bool judge(int cx,int cy,int len) {
    return judge(cx-len+1,cy-len+1,cx+len-1,cy+len-1);
}

inline int bin(int cx,int cy) { // assert n <<= 1 and m <<= 1 .
    int l = 1 , r = std::min( std::min(cx,n-cx+1) , std::min(cy,m-cy+1) ) , mid;
    if( judge(cx,cy,r) ) return r;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(cx,cy,mid) ) l = mid;
        else r = mid;
    }
    return l;
}

inline void geth(uint dst[maxn][maxn],int sx,int sy,int dx,int dy) {
    #define lx(x) (0<x&&x<=n)
    #define ly(y) (0<y&&y<=m)
    for(int i=sx;lx(i);i+=dx) for(int j=sy;ly(j);j+=dy) dst[i][j] += dst[i][j-dy] * basex;
    for(int i=sx;lx(i);i+=dx) for(int j=sy;ly(j);j+=dy) dst[i][j] += dst[i-dx][j] * basey;
}
inline void getpows(uint* dst,const uint &base,int len) {
    *dst = 1;
    for(int i=1;i<=len;i++) dst[i] = dst[i-1] * base;
}


inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline uint getint() {
    uint ret = 0;
    char ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    n = ( n << 1 ) + 1 , m = ( m << 1 ) + 1;
    getpows(powsx,basex,n) , getpows(powsy,basey,m);
    for(int i=2;i<=n;i+=2) for(int j=2;j<=m;j+=2) h[0][i][j] = h[1][i][j] = h[2][i][j] = h[3][i][j] = getint();
    geth(h[0],1,1,1,1) , geth(h[1],1,m,1,-1) , geth(h[2],n,1,-1,1) , geth(h[3],n,m,-1,-1);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( ( i & 1 ) == ( j & 1 ) )ans += ( ( bin(i,j) - (i&1) ) >> 1 );
    printf("%d\n",ans);
    return 0;
}
