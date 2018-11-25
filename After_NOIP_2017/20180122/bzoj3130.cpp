#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e2+1e1,maxm=1e3+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<4],nxt[maxm<<4],f[maxm<<4];
int dep[maxn];
int n,m,st,ed;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}

inline bool bfs() {
    memset(dep,-1,sizeof(dep)); dep[st] = 0;
    queue<int> q; q.push(st);
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
    if( pos == ed ) return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(f[at],flow));
            ret += now , flow -= now,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() )
        while( now = dfs(st,inf) )
            ret += now;
    return ret;
}

int main() {
    scanf("%d%d%*d",&n,&m);
    st = 1 , ed = n;
    for(int i=1,a,b,f;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&f);
        singledge(a,b,f);
    }
    
    printf("%d\nnan\n",dinic());
    return 0;
}