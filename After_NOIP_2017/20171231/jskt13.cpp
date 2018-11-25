#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=6e4+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<4],nxt[maxn<<4],f[maxn<<4];
int dep[maxn];
int n,m,st,ed,ans;

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
                dep[t[at]] = dep[pos] + 1;
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

int main() {
    scanf("%d%d",&n,&m);
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1,d;i<=n;i++) {
        scanf("%d",&d);
        addedge(i,ed,d);
    }
    //debug<<"cost inited"<<endl;
    for(int i=1,a,b,c;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&c);
        ans += c;
        addedge(st,i+n,c);
        addedge(i+n,a,inf);
        addedge(i+n,b,inf);
    }
    
    ans -= dinic();
    
    printf("%d\n",ans);
    
    return 0;
}