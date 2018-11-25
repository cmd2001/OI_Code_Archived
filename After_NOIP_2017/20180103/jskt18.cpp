#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=2e2+1e1,maxm=1e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<2],nxt[maxm<<2],f[maxm<<2];
int dep[maxn],deg[maxn];
int x[maxm],y[maxm],tpe[maxm];
int n,m,st,ed,full;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow);
    coredge(to,from,0);
}
inline void doubledge(int from,int to,int flow) {
    coredge(from,to,flow);
    coredge(to,from,flow);
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
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",x+i,y+i,tpe+i),
        --deg[x[i]],++deg[y[i]];
    for(int i=1;i<=n;i++)
        if( deg[i] & 1 )
            return puts("impossible"),0;
    
    st = n + 1 , ed = n + 2;
    for(int i=1;i<=n;i++)
        if( deg[i] > 0 )
            singledge(st,i,deg[i]>>1),
            full += ( deg[i] >> 1 );
        else if( deg[i] < 0 )
            singledge(i,ed,(-deg[i])>>1);
    for(int i=1;i<=m;i++)
        if( !tpe[i] )
            doubledge(x[i],y[i],1);
    
    puts(dinic()==full?"possible":"impossible");
    
    return 0;
}