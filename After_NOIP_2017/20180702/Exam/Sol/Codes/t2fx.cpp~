#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=4e3+1e2,maxe=8e3+1e2;
const int inf=0x3f3f3f3f;

int u[maxn],v[maxn],deg[maxn];
int n1,n2,m,mi=inf;

namespace NetworkFlow {
    int s[maxn],t[maxe],nxt[maxe],f[maxe],cnt;
    int dep[maxn],st,ed;
    inline void coredge(int from,int to,int flow) {
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
            }
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] +=  now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , cnt = 1;
    }
}

inline void build(int k) {
    NetworkFlow::reset() , NetworkFlow::st = n1 + n2 + 1 , NetworkFlow::ed = n1 + n2 + 2;
    for(int i=1;i<=m;i++) NetworkFlow::singledge(n1+v[i],u[i],1);
    for(int i=1;i<=n1;i++) NetworkFlow::singledge(i,NetworkFlow::ed,deg[i]-k);
    for(int i=n1+1;i<=n1+n2;i++) NetworkFlow::singledge(NetworkFlow::st,i,deg[i]-k);
}
inline void printans() {
    static int seq[maxn],sql; sql = 0;
    using namespace NetworkFlow; dinic();
    for(int i=1;i<=m;i++) if( f[i<<1] ) seq[++sql] = i;
    sort(seq+1,seq+1+sql) , printf("%d ",sql);
    for(int i=1;i<=sql;i++) printf("%d ",seq[i]);
    putchar('\n');
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n1 = getint() , n2 = getint() , m = getint();
    for(int i=1;i<=m;i++) ++deg[u[i]=getint()] , ++deg[n1+(v[i]=getint())];
    for(int i=1;i<=n1+n2;i++) mi = min( mi , deg[i] );
    for(int i=0;i<=mi;i++) build(i) , printans();
    return 0;
}

