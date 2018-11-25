#include<cstdio>
#include<set>
typedef long long int lli;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],dfn[maxn],rec[maxn];
lli l[maxn<<1],dis[maxn];
bool ins[maxn];
std::set<int> app;

inline void addedge(int from,int to,int len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , dis[t[at]] = dis[pos] + l[at] , fa[t[at]] = pos , pre(t[at]) ,
        siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos] ;
    }
}
inline void dfs(int pos) {
    static int dd;
    top[rec[dfn[pos]=++dd]=pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}
inline lli gdis(int x,int y) {
    return dis[x] + dis[y] - ( dis[lca(x,y)] << 1 );
}
inline int gprv(int x) {
    if( !app.size() ) return x; // make a self ring .
    std::set<int>::iterator it = app.lower_bound(dfn[x]);
    if( it == app.begin() ) return rec[*app.rbegin()];
    else return rec[*--it];
}
inline int gnxt(int x) {
    if( !app.size() ) return x;
    std::set<int>::iterator it = app.upper_bound(dfn[x]);
    if( it == app.end() ) return rec[*app.begin()];
    return rec[*it];
}

int main() {
    static int n,m;
    static long long int ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , addedge(b,a,l);
    pre(1) , dfs(1);
    for(int i=1,l,r,t;i<=m;i++) {
        scanf("%d",&t) , l = gprv(t) , r = gnxt(t);
        if( !ins[t] ) ans += gdis(l,t) + gdis(t,r) - gdis(l,r) , ins[t] = 1 , app.insert(dfn[t]);
        else ans -= gdis(l,t) + gdis(t,r) - gdis(l,r) , ins[t] = 0 , app.erase(dfn[t]);
        printf("%lld\n",ans);
    }
    return 0;
}
