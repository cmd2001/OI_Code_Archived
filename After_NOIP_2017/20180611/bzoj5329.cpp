#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=2e5+1e2,maxe=2e5+1e2;

int n,tot;
int dis[maxn],dfn[maxn];

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],dd;
    inline void coredge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void pre(int pos) {
        dis[pos] = dis[fa[pos]] + ( pos <= n ) , dep[pos] = dep[fa[pos]] + 1;
        dfn[pos] = ++dd , siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , pre(t[at]) , siz[pos] += siz[t[at]];
            son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
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
    inline void reset() {
        memset(s,0,sizeof(s)) , memset(son,0,sizeof(son)) , dd = cnt = 0;
    }
}
using Tree::lca;

namespace Cactus {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],cnt;
    int dfn[maxn],low[maxn],dd;
    int stk[maxn],ins[maxn],top;
    inline void coredge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void dfs(int pos) {
        low[pos] = dfn[pos] = ++dd , ins[stk[++top]=pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) {
            if( !dfn[t[at]] ) {
                dfs(t[at]) , low[pos] = min( low[pos] , low[t[at]] );
                if( low[t[at]] >= dfn[pos] ) {
                    Tree::addedge(++tot,pos);
                    do {
                        ins[stk[top]] = 0 , Tree::addedge(tot,stk[top--]);
                    } while( ins[t[at]]);
                }
            } else low[pos] = min( low[pos] , dfn[t[at]] );
        }
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , memset(dfn,0,sizeof(dfn)) , dd = cnt = 0;
    }
}

namespace VirtualTree {
    int in[maxn],stk[maxn],top,k;
    lli ans;
    inline bool cmp(int x,int y) {
        return dfn[x] < dfn[y];
    }
    inline void solve_case() {
        scanf("%d",&k) , ans = top = 0;
        for(int i=1;i<=k;i++) scanf("%d",in+i);
        sort(in+1,in+1+k,cmp);
        for(int i=1;i<=k;i++) {
            const int p = in[i];
            if( !top ) stk[++top] = p;
            else {
                const int l = lca(stk[top],p);
                while( dfn[l] < dfn[stk[top]] ) {
                    if( top == 1 || dfn[stk[top-1]] <= dfn[l] ) {
                        ans += dis[stk[top--]] - dis[l];
                        if( stk[top] != l ) stk[++top] = l;
                        break;
                    } else ans += dis[stk[top]] - dis[stk[top-1]] , --top;
                } stk[++top] = p;
            }
        }
        while( top > 1 ) ans += dis[stk[top]] - dis[stk[top-1]] , --top;
        if( top && stk[top] <= n ) ++ans;
        printf("%lld\n",ans-k);
    }
}

int main() {
    static int T,m,q;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m) , tot = n , Tree::reset() , Cactus::reset();
        for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , Cactus::addedge(a,b);
        Cactus::dfs(1) , Tree::pre(1) , Tree::dfs(1) , scanf("%d",&q);
        while(q--) VirtualTree::solve_case();
    }
    return 0;
}
