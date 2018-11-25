#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
const int maxn=1e7+1e2;
const int inf=0x3f3f3f3f;

int x[maxn],y[maxn],w[maxn];
int sx=inf,tx,sy=inf,ty;
bitset<maxn> ans,vis;
int n,sum=inf;
long long int len;

inline void update(int x,int y) {
    sx = min( sx , x ) , tx = max( tx , x ) ,
    sy = min( sy , y ) , ty = max( ty , y );
}

inline void check(int sx,int tx,int sy,int ty) {
    int ret = 0;
    vis &= 0;
    for(int i=1;i<=n;i++) {
        if( sx <= x[i] && x[i] <= tx && sy <= y[i] && y[i] <= ty ) continue;
        else if( sx <= y[i] && y[i] <= tx && sy <= x[i] && x[i] <= ty ) vis[i] = 1 , ret += w[i];
        else return;
    }
    if( ret  < sum ) {
        sum = ret , ans = vis;
    }
}
inline char nextchar() {
    #define BUFSIZE (1<<23)
    static char buf[BUFSIZE],*st=buf+BUFSIZE,*ed=buf+BUFSIZE;
    if( st == ed ) ed = buf + fread( st = buf , 1 , BUFSIZE , stdin );
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch ;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
int main() {
    n = getint();
    for(int i=1;i<=n;i++) {
        x[i] = getint() , y[i] = getint() , w[i] = getint();
        if( x[i] <= y[i] ) update(x[i],y[i]);
        else update(y[i],x[i]);
    }
    len = ( tx - sx + ty - sy );
    check(sx,tx,sy,ty) , check(sx,ty,sy,tx) ,
    check(sy,tx,sx,ty) , check(sy,ty,sx,tx) ;
    printf("%lld %d\n",len*2LL,sum);
    for(int i=1;i<=n;i++)
        putchar('0'+ans[i]);
    putchar('\n');
    return 0;
}
