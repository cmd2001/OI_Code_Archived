#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1.2e3+1e2,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn<<2],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],dep[maxn<<1],cur[maxn<<1];
int n,m,st,ed,ans;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}
inline bool bfs() {
    memset(dep,-1,sizeof(dep)) , dep[st] = 0;
    queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0;
    for(cur[pos]=cur[pos]?cur[pos]:s[pos];cur[pos];cur[pos]=nxt[cur[pos]])
        if( f[cur[pos]] && dep[t[cur[pos]]] > dep[pos] ) {
            cur[pos] = cur[pos];
            now = dfs(t[cur[pos]],min(flow,f[cur[pos]]));
            ret += now , flow -= now ,
            f[cur[pos]] -= now , f[cur[pos]^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() ) {
        memset(cur,0,sizeof(cur));
        while( now = dfs(st,inf) ) ret += now;
    }
    return ret;
}


int main() {
    scanf("%d%d",&n,&m) , st = n + m + 1 , ed = st + 1;
    for(int i=1,x,t,u,v;i<=n;i++) {
        scanf("%d%d",&x,&t) , ans += x , singledge(st,i,x);
        while(t--) {
            scanf("%d%d",&u,&v);
            singledge(i,u+n,v);
        }
    }
    for(int i=1,x;i<=m;i++) {
        scanf("%d",&x) , singledge(i+n,ed,x);
    }
    ans -= dinic();
    printf("%d\n",ans);
    return 0;
}

