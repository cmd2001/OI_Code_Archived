#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxm=2e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn<<1],t[maxm<<3],nxt[maxm<<3],f[maxm<<3],cnt;
int dep[maxn<<1];
int n,m,st,ed;

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int from,int to,int flow) {
    coredge(from,to,flow);
    coredge(to,from,0);
}

inline bool bfs() {
    memset(dep,-1,sizeof(dep));
    dep[st] = 0;
    queue<int> q;
    q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1,
                q.push(t[at]);
            }
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    if( pos == ed )
        return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at]));
            ret += now , flow -= now,
            f[at] -= now , f[at^1] += now;
            if( !flow )
                return ret;
        }
    if( !ret )
        dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

inline int cov(int id,int sta) {
    return ( id << 1 ) - 1 + sta;
}

inline void init() {
    for(int i=0;i<=ed;i++)
        s[i] = 0;
    cnt = 1;
}

inline int getint() {
    int ret = 0 , ch = getchar();
    while( !isdigit(ch) )
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ( ch - '0' ),
        ch = getchar();
    return ret;
}

int main() {
    while( scanf("%d%d",&n,&m) == 2 ) {
        init();
        st = ( n << 1 ) + 1 , ed = st + 1;
        for(int i=1;i<=n;i++) {
            addedge(st,cov(i,0),1);
            addedge(cov(i,1),ed,1);
        }
        for(int i=1,a,b;i<=m;i++) {
            a = getint() , b = getint();
            addedge(cov(a,0),cov(b,1),1);
        }
        puts(dinic()==n?"YES":"NO");
    }
    
    return 0;
}