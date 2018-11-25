#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=2e5+1e2;

int n,tot;
int val[maxn];
lli ans;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],siz[maxn],fs;
    bool vis[maxn];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void pre(int pos) {
        siz[pos] = pos <= n , vis[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( !vis[t[at]] ) pre(t[at]) , siz[pos] += siz[t[at]];
    }
    inline void dfs(int pos,int fa) {
        ans += (lli) val[pos] * ( fs - siz[pos] ) * siz[pos] << 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
            dfs(t[at],pos) , ans += (lli) val[pos] * siz[t[at]] * ( siz[pos] - siz[t[at]] + ( pos <= n ) );
        }
    }
    inline void getans() {
        for(int i=1;i<=n;i++) val[i] = -1;
        for(int i=1;i<=n;i++) if( !vis[i] ) {
            pre(i) , fs = siz[i] , dfs(i,-1);
        }
    }
}

namespace Graph {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int low[maxn],dfn[maxn],stk[maxn],dd,top;
    bool ins[maxn],vis[maxn];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void dfs(int pos) {
        low[pos] = dfn[pos] = ++dd , vis[pos] = ins[stk[++top]=pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) {
            if( !dfn[t[at]] ) {
                dfs(t[at]) , low[pos] = std::min(low[pos],low[t[at]]);
                if( low[t[at]] >= dfn[pos] ) {
                    Tree::addedge(pos,++tot) , ++val[tot];
                    do {
                        const int x = stk[top--]; ins[x] = 0;
                        Tree::addedge(x,tot) , ++val[tot];
                    } while( ins[t[at]] );
                }
            } else low[pos] = std::min(low[pos],dfn[t[at]]);
        }
    }
}

int main() {
    static int m;
    scanf("%d%d",&n,&m) , tot = n;
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , Graph::addedge(a,b);
    for(int i=1;i<=n;i++) if( !Graph::vis[i] ) Graph::dfs(i);
    Tree::getans() , printf("%lld\n",ans);
    return 0;
}
