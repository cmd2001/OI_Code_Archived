#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=2e4+1e2,maxe=2e5+2e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2];
int dep[maxn],st,ed;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}
inline void doubledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,flow);
}

inline bool bfs() {
    memset(dep,-1,sizeof(dep)) , dep[st] = 0;
    queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] )
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at])) ,
            ret += now , flow -= now,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() ) while( now = dfs(st,inf) ) ret += now;
    return ret;
}


int main() {
    static int n,m;
    scanf("%d%d",&n,&m) , st = n + 1 , ed = st + 1;
    for(int i=1,a,b;i<=n;i++) scanf("%d%d",&a,&b) , singledge(st,i,a) , singledge(i,ed,b);
    for(int i=1,x,y,w;i<=m;i++) scanf("%d%d%d",&x,&y,&w) , doubledge(x,y,w);
    printf("%d\n",dinic());
    return 0;
}
