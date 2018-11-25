#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],s[maxn],stk[maxn],ans[maxn],top;

struct Query {
    int x,y,id;
    friend bool operator < (const Query &a,const Query &b) {
        return a.y < b.y;
    }
}qs[maxn];

__inline int f(int p) {
    return in[p] * p - s[p];
}
__inline double slop(int i,int j) { // assert i < j && in[i] < in[j] .
    return ( (double) f(j) - f(i) ) / ( (double) in[j] - in[i] );
}
__inline int calc(int p,int x,int y) {
    return s[y] + f(p) + ( x - y ) * in[p];
}
__inline int tri(int l,int r,int x,int y) {
    int lmid,rmid,cl,cr,ret=inf;
    while( r > l + 2 ) {
        lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3 ,
        cl = calc(stk[lmid],x,y) , cr = calc(stk[rmid],x,y);
        if( cl > cr ) l = lmid;
        else r = rmid;
    }
    for(int i=l;i<=r;i++) ret = std::min( ret , calc(stk[i],x,y) );
    return ret;
}

__inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
__inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int n,m;
    n = getint();
    for(int i=1;i<=n;i++) s[i] = s[i-1] + ( in[i] = getint() );
    m = getint();
    for(int i=1;i<=m;i++) qs[i].x = getint() , qs[i].y = getint() , qs[i].id = i;
    std::sort(qs+1,qs+1+m);
    for(int i=1,j=1;i<=n;i++) {
        while( top && in[stk[top]] >= in[i] ) --top;
        while( top > 1 && slop(i,stk[top]) <= slop(stk[top],stk[top-1]) ) --top;
        stk[++top] = i;
        while( j <= m && qs[j].y == i ) ans[qs[j].id] = tri(std::upper_bound(stk+1,stk+1+top,qs[j].y-qs[j].x)-stk,top,qs[j].x,qs[j].y) , ++j;
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}
