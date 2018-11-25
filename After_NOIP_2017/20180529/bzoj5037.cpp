#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
const int maxn=5e2+1e2;
const int inf=0x3f3f3f3f;

int x[maxn],y[maxn],r[maxn],s[maxn];
int n,ans;

namespace NetworkFlow {
    int s[maxn],t[maxn*maxn<<2],nxt[maxn*maxn<<2],f[maxn*maxn<<2];
    int dep[maxn],st,ed;

    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
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
        int ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
}

inline int dis(int x,int y,int xx,int yy) {
    const int dx = x - xx , dy = y - yy;
    return dx * dx + dy * dy;
}
inline void build() {
    using NetworkFlow::singledge;
    using NetworkFlow::st;
    using NetworkFlow::ed;
    st = n + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) {
        if( s[i] > 0 ) singledge(st,i,s[i]) , ans += s[i];
        else singledge(i,ed,-s[i]);
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if( i != j && dis(x[i],y[i],x[j],y[j]) <= r[i] * r[i] ) singledge(i,j,inf);
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d%d",x+i,y+i,r+i,s+i);
    build() , printf("%d\n",ans-NetworkFlow::dinic());
    return 0;
}
