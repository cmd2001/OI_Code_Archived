int dfn[maxn],dep[maxn];
namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int fa[maxn],siz[maxn],son[maxn],top[maxn];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void pre(int pos) {
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]);
            siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
    }
    inline void dfs(int pos) {
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs(t[at]);
    }
    inline int lca(int x,int y) {
        while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
        return dep[x] < dep[y] ? x : y;
    }
}
using Tree::lca;


bool sel[maxn];
namespace VirtualTree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],
}



inline bool cmp(int x,int y) {
    return dfn[x] < dfn[y];
}
