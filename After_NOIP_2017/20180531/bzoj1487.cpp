#include<cstdio>
#include<algorithm>
const int maxn=1e5+1e2,maxe=2e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<1],nxt[maxe<<1];
int fa[maxn],dfn[maxn],low[maxn],dd;
int in[maxn],f[maxn][2];

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline void solve(int rt,int pos) {
    static int rng[maxn],g[maxn][2],p[2],cnt;
    p[0] = p[1] = cnt = 0;
    for(int i=pos;i!=fa[rt];i=fa[i]) rng[++cnt] = i;
    g[1][0] = f[pos][0] , g[1][1] = -inf;
    for(int i=2;i<=cnt;i++) {
        g[i][0] = f[rng[i]][0] + std::max(g[i-1][0],g[i-1][1]) ,
        g[i][1] = f[rng[i]][1] + g[i-1][0];
    }
    p[0] = g[cnt][0] , p[1] = g[cnt][1];
    g[1][0] = f[pos][0] , g[1][1] = f[pos][1];
    for(int i=2;i<=cnt;i++) {
        g[i][0] = f[rng[i]][0] + std::max(g[i-1][0],g[i-1][1]) ,
        g[i][1] = f[rng[i]][1] + g[i-1][0];
    }
    p[0] = std::max(p[0],g[cnt][0]);
    f[rt][0] = std::max(f[rt][0],p[0]) , f[rt][1] = std::max(f[rt][1],p[1]);
}
inline void dfs(int pos) {
    low[pos] = dfn[pos] = ++dd , f[pos][1] = in[pos];
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        if( !dfn[t[at]] ) {
            fa[t[at]] = pos , dfs(t[at]) , low[pos] = std::min(low[pos],low[t[at]]);
            if( low[t[at]] > dfn[pos] ) f[pos][0] += std::max(f[t[at]][0],f[t[at]][1]) , f[pos][1] += f[t[at]][0];
        } else low[pos] = std::min(low[pos],dfn[t[at]]);
    }
    for(int at=s[pos];at;at=nxt[at]) if( fa[t[at]] != pos && dfn[t[at]] > dfn[pos] ) solve(pos,t[at]);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    dfs(1) , printf("%d\n",std::max(f[1][0],f[1][1]));
    return 0;
}
