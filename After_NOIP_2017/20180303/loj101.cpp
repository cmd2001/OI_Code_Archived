#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define lli long long int
const int maxn=1e6+1e2,maxe=4e6+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

namespace IO {
    const int bs = 1 << 25;
    inline char nextchar() {
        static char buf[bs],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,bs,stdin);
        return st == ed ? -1 : *st++;
    }
    inline int getint() {
        int ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using IO::getint;
struct Queue {
    const static int sz=1048575;
    int dat[maxn+1],st,ed;
    Queue() {
        st = 1;
    }
    inline void push(const int x) {
        ed = ( ed + 1 ) & sz;
        dat[ed] = x;
    }
    inline int front() {
        return dat[st];
    }
    inline void pop() {
        st = ( st + 1 ) & sz;
    }
    inline int size() {
        return st != ( ( ed + 1 ) & sz );
    }
}q;

int s[maxn],t[maxe],nxt[maxe];
lli f[maxe];
int dep[maxn],cur[maxn];
int n,m,st,ed;

inline void coredge(int from,int to,lli flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,lli flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}
inline bool bfs() {
    memset(dep+1,-1,sizeof(int)*n) , dep[st] = 0;
    q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] )
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
    }
    return ~dep[ed];
}
inline lli dfs(int pos,lli flow) {
    if( pos == ed ) return flow;
    lli ret = 0 , now = 0;
    for(int at=cur[pos]?cur[pos]:s[pos];at;at=nxt[at]) {
        cur[pos] = at;
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],std::min(flow,f[at]));
            ret += now , flow -= now ,
            f[at] -= now ,f[at^1] += now;
            if( !flow ) return ret;
        }
    }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline lli dinic() {
    lli ret = 0 , now = 0;
    while( bfs() ) {
        memset(cur+1,0,sizeof(int)*n);
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

int main() {
    n = getint() , m = getint() , st = getint() , ed = getint();
    for(int i=1,u,v,w;i<=m;i++) {
        u = getint() , v = getint() , w = getint();
        singledge(u,v,w);
    }
    printf("%lld\n",dinic());
    return 0;
}
