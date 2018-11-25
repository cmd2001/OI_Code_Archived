#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("avx")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define bool unsigned char
const unsigned maxn=1e4+1e2+3,maxs=(1<<9)+5,maxq=11;
const unsigned inf=0x3f3f3f3f;
// I know it's impossible for me to AC this problem in 1.5s, but I have to try.

unsigned s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
unsigned f[maxs][maxn],g[maxs],pts[maxq];
unsigned n,m,d,full;

__inline void addedge(unsigned from,unsigned to,unsigned len) {
    static unsigned cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
__inline void spfa(unsigned* dis) {
    static bool inq[maxn];
    static std::queue<unsigned> q;
    for(unsigned i=1;i<=n;i++) if( dis[i] != inf ) q.push(i) , inq[i] = 1;
    while( q.size() ) {
        const unsigned pos = q.front(); q.pop() , inq[pos] = 0;
        for(register unsigned at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
}
__inline void getf() {
    memset(f,0x3f,sizeof(f));
    for(register unsigned i=0;i<(d<<1);i++) f[1<<i][pts[i]] = 0;
    for(register unsigned sta=0;sta<full;sta++) {
        for(register unsigned ss=sta;ss;ss=(ss-1)&sta)
            for(register unsigned i=1;i<=n;i++)
                f[sta][i] = std::min( f[sta][i] , f[ss][i] + f[sta^ss][i] );
        spfa(f[sta]);
    }
}
__inline bool legal(unsigned sta) {
    for(register unsigned i=0;i<=(d<<1);i++)
        if( ( ( sta >> i ) & 1 ) != ( sta >> ( ( d << 1 ) - i - 1 ) & 1 ) ) return 0;
    return 1;
}
__inline void getg() {
    memset(g,0x3f,sizeof(g));
    for(register unsigned sta=0;sta<full;sta++) if( legal(sta) ) for(register unsigned i=1;i<=n;i++) g[sta] = std::min( g[sta] , f[sta][i] );
    for(register unsigned sta=0;sta<full;sta++) for(register unsigned ss=sta;ss;ss=(ss-1)&sta) g[sta] = std::min( g[sta] , g[ss] + g[sta^ss] );
}

__inline unsigned char nextchar() {
    static const unsigned BS = 1 << 22;
    static unsigned char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
__inline unsigned getint() {
    register unsigned ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint() , full = 1 << ( ( d = getint() ) << 1 );
    for(register unsigned i=1,a,b,l;i<=m;i++) a = getint() , b = getint() , l = getint() , addedge(a,b,l) , addedge(b,a,l);
    for(register unsigned i=0;i<d;i++) pts[i] = i + 1 , pts[(d<<1)-i-1] = n - i;
    getf() , getg();
    if( g[full-1] == inf ) puts("-1");
    else printf("%u\n",g[full-1]);
    return 0;
}
