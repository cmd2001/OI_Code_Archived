#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int maxn=5e3+1e1,maxq=1e4+1e2,maxe=2e6+1e2;
const int inf=0x3f3f3f3f;

struct Query { int tar,id; };
vector<Query> qs[maxq];
int ans[maxq];
int n,m,cnt;

namespace Graph {
    int s[maxn<<1],t[maxe],nxt[maxe],l[maxe];
    int dis[maxn<<1];
    bool inq[maxn<<1];
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,0);
    }
    inline void spfa(int st) {
        memset(dis,0x3f,(n+m)<<2) , dis[st] = 0;
        queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
        }
        for(unsigned i=0;i<qs[st].size();i++) ans[qs[st][i].id] = dis[qs[st][i].tar] == inf ? -1 : dis[qs[st][i].tar];
    }
}
namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],fa[maxn],dep[maxn];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void dfs(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , dfs(t[at]);
    }
}

inline void build(int u,int v) {
    using Tree::fa; using Tree::dep; using Graph::addedge; ++cnt;
    while( u != v ) {
        if( dep[u] < dep[v] ) swap(u,v);
        addedge(cnt,u,1) , u = fa[u];
    }
    addedge(cnt,u,1);
}

int main() {
    static int q;
    freopen("go.in","r",stdin);
    freopen("go.out","w",stdout);
    scanf("%d",&n);
    for(int i=2,p;i<=n;i++) scanf("%d",&p) , Tree::addedge(p,i);
    scanf("%d",&m) , cnt = n , Tree::dfs(1);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , build(a,b);
    scanf("%d",&q);
    for(int i=1,u,v;i<=q;i++) scanf("%d%d",&u,&v) , qs[min(u,v)].push_back((Query){max(u,v),i});
    for(int i=1;i<=n;i++) if( qs[i].size() ) Graph::spfa(i);
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    fclose(stdout);
    return 0;
}
