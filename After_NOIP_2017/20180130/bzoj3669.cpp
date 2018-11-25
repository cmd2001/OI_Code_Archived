#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define bool unsigned char
using namespace std;
const int maxn=5e4+1e2,maxm=1e5+1e2;
const int inf=0x3f3f3f3f;

struct Edge {
    int x,y,a,b;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.a < b.a;
    }
}es[maxm];

int s[maxn],t[maxm<<1],nxt[maxm<<1],l[maxm<<1];
int dis[maxn];
bool inq[maxn];

struct Queue {
    const static int len = 65536 , mask = len - 1;
    int dat[65536+3],st,ed;
    inline bool empty() {
        return ed == st;
    }
    inline void push(int x) {
        ed = ( ed + 1 ) & mask;
        dat[ed] = x;
    }
    inline int pop() {
        st = ( st + 1 ) & mask;
        return dat[st];
    }
}q;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void spfa() {
    while( !q.empty() ) {
        const int pos = q.pop(); inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > max( dis[pos] , l[at] ) ) {
                dis[t[at]] = max( dis[pos] , l[at] );
                if( !inq[t[at]] ) {
                    q.push(t[at]);
                    inq[t[at]] = 1;
                }
            }
    }
}
inline void pushque(int x,int y,int b) {
    if( dis[y] > max( dis[x] , b ) ) {
        dis[y] = max( dis[x] , b );
        if( !inq[y] ) q.push(y) , inq[y] = 1;
    }
}
inline int add(int m) {
    static int ptr = 1;
    if( ptr > m ) return -1;
    addedge(es[ptr].x,es[ptr].y,es[ptr].b);
    addedge(es[ptr].y,es[ptr].x,es[ptr].b);
    pushque(es[ptr].x,es[ptr].y,es[ptr].b);
    pushque(es[ptr].y,es[ptr].x,es[ptr].b);
    ++ptr;
    while( ptr <= m && es[ptr].a == es[ptr-1].a ) {
        addedge(es[ptr].x,es[ptr].y,es[ptr].b);
        addedge(es[ptr].y,es[ptr].x,es[ptr].b);
        pushque(es[ptr].x,es[ptr].y,es[ptr].b);
        pushque(es[ptr].y,es[ptr].x,es[ptr].b);
        ++ptr;
    }
    return es[ptr-1].a;
}

inline char nextchar() {
    #define BS (1<<21)
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread( st = buf , 1 , BS , stdin );
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
int main() {
    static int n,m,ans=inf,t;
    n = getint() , m = getint();
    for(register int i=1;i<=m;++i)
        es[i].x = getint() , es[i].y = getint() , es[i].a = getint() , es[i].b = getint();
    sort(es+1,es+1+m);
    memset(dis,0x3f,sizeof(dis)) , dis[1] = 0;
    while(  ~ ( t = add(m) ) ) {
        spfa();
        ans = min( ans , t + dis[n] );
    }
    if( ans == inf ) puts("-1");
    else printf("%d\n",ans);
    return 0;
}

