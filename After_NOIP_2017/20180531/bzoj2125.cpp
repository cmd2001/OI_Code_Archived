#include<cstdio>
#include<algorithm>
const int maxn=2e4+1e2;

int rid[maxn],rsum[maxn];
int n,tot;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
    int dep[maxn],dis[maxn],anc[maxn][16];
    
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void dfs(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != *anc[pos] ) {
            dep[t[at]] = dep[pos] + 1 , dis[t[at]] = dis[pos] + l[at] , *anc[t[at]] = pos;
            dfs(t[at]);
        }
    }
    inline void pre() {
        for(int j=1;j<16;j++) for(int i=1;i<=tot;i++) anc[i][j] = anc[anc[i][j-1]][j-1];
    }
    inline int lca(int x,int y,int &nx,int &ny) {
        if( dep[x] < dep[y] ) std::swap(x,y);
        for(int i=15;~i;i--) if( dep[x] - ( 1 << i ) >= dep[y] ) x = anc[x][i];
        if( x == y ) return x; // x must be a circle point because we will never query square point .
        for(int i=15;~i;i--) if( anc[x][i] != anc[y][i] ) x = anc[x][i] , y = anc[y][i];
        nx = x , ny = y;
        return *anc[x];
    }
}

namespace Catus {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
    int dfn[maxn],low[maxn],fa[maxn],dtfa[maxn],dd;
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void solve(int ed,int st,int su) {
        int cnt = 0; ++tot;
        for(int i=ed;i!=fa[st];i=fa[i]) {
            rid[i] = ++cnt , rsum[i] = su;
            if( i != st ) su += dtfa[i];
        }
        rsum[tot] = su;
        for(int i=ed;i!=fa[st];i=fa[i]) Tree::addedge(tot,i,std::min(rsum[i],su-rsum[i]));
    }
    inline void tarjan(int pos) {
        low[pos] = dfn[pos] = ++dd;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            if( !dfn[t[at]] ) {
                fa[t[at]] = pos , dtfa[t[at]] = l[at] , 
                tarjan(t[at]) , low[pos] = std::min(low[pos],low[t[at]]);
            } else low[pos] = std::min(low[pos],dfn[t[at]]);
            if( low[t[at]] > dfn[pos] ) Tree::addedge(pos,t[at],l[at]);
        }
        for(int at=s[pos];at;at=nxt[at]) if( fa[t[at]] != pos && dfn[t[at]] > dfn[pos] ) solve(t[at],pos,l[at]);
    }
}

inline int getans(int x,int y) {
    using namespace Tree;
    static int lc,nx,ny;
    lc = lca(x,y,nx,ny);
    if( lc <= n ) return dis[x] + dis[y] - ( dis[lc] << 1 );
    else {
        int ret = dis[x] + dis[y] - dis[nx] - dis[ny];
        if( rid[nx] > rid[ny] ) std::swap(nx,ny);
        ret += std::min( rsum[ny] - rsum[nx] , rsum[lc] - rsum[ny] + rsum[nx] );
        return ret;
    }
}

int main() {
    static int m,q;
    scanf("%d%d%d",&n,&m,&q) , tot = n;
    for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , Catus::addedge(a,b,l);
    Catus::tarjan(1) , Tree::dfs(1) , Tree::pre();
    for(int i=1,a,b;i<=q;i++) scanf("%d%d",&a,&b) , printf("%d\n",getans(a,b));
    return 0;
}
