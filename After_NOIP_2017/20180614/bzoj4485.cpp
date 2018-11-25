#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1.6e5+1e2,maxl=4e2+1e1;
const int inf=0x3f3f3f3f;

namespace NetworkFlow {
    int s[maxn],t[maxn<<4],nxt[maxn<<4],f[maxn<<4];
    int dep[maxn],st,ed;
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
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
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
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
}
using NetworkFlow::st;
using NetworkFlow::ed;
using NetworkFlow::singledge;
using NetworkFlow::doubledge;
using NetworkFlow::dinic;

int n,m,t,ans;

inline int cov(int x,int y) {
    return m * --x + y;
}

int main() {
    scanf("%d%d",&n,&m) , st = n * m + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
        scanf("%d",&t);
        if( t > 0 ) ans += t , singledge(st,cov(i,j),t);
        else if( t < 0 ) ans -= t , singledge(cov(i,j),ed,-t);
    }
    for(int i=1;i<n;i++) for(int j=1;j<=m;j++) scanf("%d",&t) , doubledge(cov(i,j),cov(i+1,j),t);
    for(int i=1;i<=n;i++) for(int j=1;j<m;j++) scanf("%d",&t) , doubledge(cov(i,j),cov(i,j+1),t);
    ans -= dinic() , printf("%d\n",ans);
    return 0;
}
