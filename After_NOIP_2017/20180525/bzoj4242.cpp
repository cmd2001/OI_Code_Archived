#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
const int maxn=2e3+1e2,maxp=2e5+1e2,maxl=20;

char in[maxn][maxn];
int a[maxp],b[maxp];
int h,w,n,m;

struct UnionFindSet {
    int fa[maxp];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        return ( x = findfa(x) ) == ( y = findfa(y) ) ? 0 : fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

namespace Tree {
    int s[maxp],t[maxp<<1],nxt[maxp<<1],l[maxp<<1];
    int fa[maxp][maxl],dis[maxp][maxl],dep[maxp];
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void dfs(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != *fa[pos] ) *fa[t[at]] = pos , *dis[t[at]] = l[at] , dep[t[at]] = dep[pos] + 1 , dfs(t[at]);
    }
    inline void init() {
        for(int i=1;i<=n;i++) if( !*fa[i] ) dfs(i);
        for(int j=1;j<=19;j++) for(int i=1;i<=n;i++) fa[i][j] = fa[fa[i][j-1]][j-1] , dis[i][j] = std::max( dis[i][j-1] , dis[fa[i][j-1]][j-1] );
    }
    inline int query(int x,int y) {
        if( ufs.findfa(x) != ufs.findfa(y) ) return -1;
        int ret = 0;
        if( dep[x] < dep[y] ) std::swap(x,y);
        for(int i=19;~i;i--) if( dep[x] - ( 1 << i ) >= dep[y] ) ret = std::max( ret , dis[x][i] ) , x = fa[x][i];
        if( x == y ) return ret;
        for(int i=19;~i;i--) if( fa[x][i] != fa[y][i] ) ret = std::max( ret , std::max( dis[x][i] , dis[y][i] ) ) , x = fa[x][i] , y = fa[y][i];
        ret = std::max( ret , std::max( *dis[x] , *dis[y] ) );
        return ret;
    }
}


namespace Build {
    const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
    struct Node { int x,y; };
    struct Edge { int u,v; };
    std::vector<Edge> es[maxn*maxn];
    std::queue<Node> q;
    int bel[maxn][maxn],dis[maxn][maxn];
    inline void core_bfs(int x,int y) {
        #define legal(x,y) (0<x&&x<=h&&0<y&&y<=w)
        for(int i=0;i<4;i++) {
            const int tx = x + dx[i] , ty = y + dy[i];
            if( legal(tx,ty) && in[tx][ty] != '#' ) {
                if( !bel[tx][ty] ) bel[tx][ty] = bel[x][y] , dis[tx][ty] = dis[x][y] + 1 , q.push((Node){tx,ty});
                else if( bel[tx][ty] != bel[x][y] ) es[dis[tx][ty]+dis[x][y]].push_back((Edge){bel[tx][ty],bel[x][y]});
            }
        }
    }
    inline void work() {
        for(int i=1;i<=n;i++) bel[a[i]][b[i]] = i , q.push((Node){a[i],b[i]});
        while( q.size() ) {
            core_bfs(q.front().x,q.front().y) , q.pop();
        }
        ufs.init();
        for(int i=0;i<=w*h;i++) for(unsigned j=0;j<es[i].size();j++) if( ufs.merge(es[i][j].u,es[i][j].v) ) Tree::addedge(es[i][j].u,es[i][j].v,i);
    }
}

int main() {
    scanf("%d%d%d%d",&h,&w,&n,&m);
    for(int i=1;i<=h;i++) scanf("%s",in[i]+1);
    for(int i=1;i<=n;i++) scanf("%d%d",a+i,b+i);
    Build::work() , Tree::init();
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , printf("%d\n",Tree::query(a,b));
    return 0;
}
