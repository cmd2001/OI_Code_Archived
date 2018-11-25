#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=4e2+1e1,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<2],nxt[maxm<<2],f[maxm<<2],dep[maxn];
int n,m,k,st,ed;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
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

inline int covin(int id) {
    return id * 2 - 1;
}
inline int covout(int id) {
    return id * 2;
}
inline int covfood(int id) {
    return id + n*2;
}
inline int covdrink(int id) {
    return id + n*2 + m;
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    st = n*2 + m + k + 1 , ed = n*2 + m + k + 2;
    
    for(int i=1,a,b,x;i<=n;i++) {
        scanf("%d%d",&a,&b);
        while( a-- ) {
            scanf("%d",&x);
            addedge(covfood(x),covin(i),1);
        }
        while( b-- ) {
            scanf("%d",&x);
            addedge(covout(i),covdrink(x),1);
        }
    }
    for(int i=1;i<=n;i++)
        addedge(covin(i),covout(i),1);
    for(int i=1;i<=m;i++)
        addedge(st,covfood(i),1);
    for(int i=1;i<=k;i++)
        addedge(covdrink(i),ed,1);
    
    printf("%d\n",dinic());
    
    return 0;
}