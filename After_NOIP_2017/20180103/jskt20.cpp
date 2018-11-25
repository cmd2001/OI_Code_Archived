#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

int in[maxm],last[maxm];
int s[maxn],t[maxm<<4],nxt[maxm<<4],f[maxm<<4];
int dep[maxn];
int n,m,st,ed;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int from,int to,int flow) {
    //debug<<"edge added from = "<<from<<"to = "<<to<<"flow = "<<flow<<endl;
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
    //debug<<"bfsed ret = "<<dep[ed]<<endl;
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
    st = m + 1 , ed = m + 2;
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    for(int i=1,k,s;i<=m;i++) {
        scanf("%d",&k);
        while( k-- ) {
            scanf("%d",&s);
            if( !last[s] )
                addedge(st,i,in[s]);
            else
                addedge(last[s],i,inf);
            last[s] = i;
        }
        scanf("%d",&s);
        addedge(i,ed,s);
    }
    
    printf("%d\n",dinic());
    
    return 0;
}