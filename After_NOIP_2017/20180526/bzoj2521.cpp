#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=5e2+1e1,maxe=8e2+1e2;
const int inf=0x3f3f3f3f;

namespace NetworkFlow {
    int s[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2];
    int dep[maxn],st,ed;
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void doubledge(int a,int b,int flow) {
        coredge(a,b,flow) , coredge(b,a,flow);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        std::queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],std::min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0 , now ;
        while( bfs() ) ret += now = dfs(st,inf);
        return ret;
    }
}

int u[maxe],v[maxe],w[maxe];
int n,m,tar;

int main() {
    scanf("%d%d%d",&n,&m,&tar);
    for(int i=1;i<=m;i++) scanf("%d%d%d",u+i,v+i,w+i);
    for(int i=1;i<=m;i++) if( i != tar && w[i] <= w[tar] ) NetworkFlow::doubledge(u[i],v[i],w[tar]-w[i]+1);
    NetworkFlow::st = u[tar] , NetworkFlow::ed = v[tar] , printf("%d\n",NetworkFlow::dinic());
    return 0;
}
