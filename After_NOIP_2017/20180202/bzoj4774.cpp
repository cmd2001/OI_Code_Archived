#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define bool unsigned char
const int maxn=1e4+1e2,maxs=1<<9;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<2],nxt[maxn<<2],l[maxn<<2];
int f[maxs][maxn],g[maxs];
bool inq[maxn];
int n,q,dq,full;


inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to,int len) {
    addedge(from,to,len) , addedge(to,from,len);
}

inline void spfa(std::queue<int> &q,int* dis) {
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] )
                    q.push(t[at]) , inq[t[at]] = 1;
            }
    }
}
inline void calc() {
    static std::queue<int> que;
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<q;i++) f[1<<i][i+1] = 0;
    for(int i=q;i<dq;i++) f[1<<(dq-(i-q)-1)][n-(i-q)] = 0;
    for(int sta=0;sta<=full;sta++) {
        for(int ss=sta;ss;ss=(ss-1)&sta)
            for(int i=1;i<=n;i++)
                if( f[sta][i] > f[ss][i] + f[sta^ss][i] ) {
                    f[sta][i] = f[ss][i] + f[sta^ss][i];
                }
        for(int i=1;i<=n;i++) que.push(i) , inq[i] = 1;
        spfa( que , f[sta] );
    }
}
inline bool judge(int ss) {
    for(int i=0;i<q;i++)
        if( ( ( ss >> i ) & 1 ) != ( ( ss >> ( dq - i - 1 ) ) & 1 ) )
            return 0;
    return 1;
}
inline void calcg() {
    memset(g,0x3f,sizeof(g));
    for(int sta=0;sta<=full;sta++) {
        if( judge(sta) ) {
            for(int i=1;i<=n;i++)
                g[sta] = std::min( g[sta] , f[sta][i] );
        }
        for(int ss=sta;ss;ss=(ss-1)&sta)
            g[sta] = std::min( g[sta] , g[ss] + g[sta^ss] );
    }
}

inline char nextchar() {
    const static int bs = 262144<<1;
    static char buf[bs],*st=buf+bs,*ed=buf+bs;
    if( st == ed ) ed = buf + fread( st = buf , 1 , bs , stdin );
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int m;
    n = getint() , m = getint() , q = getint();
    dq = q << 1 , full = ( 1 << dq ) - 1;
    for(int i=1,a,b,l;i<=m;i++) {
        a = getint() , b = getint() , l = getint();
        doubledge(a,b,l);
    }
    
    calc();
    calcg();
    
    if( g[full] == inf ) puts("-1");
    else printf("%d\n",g[full]);
    
    return 0;
}
