#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1e6+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int dfn[maxn],dep[maxn];

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int fa[maxn],siz[maxn],son[maxn],top[maxn],dd;
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void pre(int pos) {
        siz[pos] = 1 , dfn[pos] = ++dd;
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
    int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
    lli l[maxn<<1],f[maxn],g[maxn];
    int siz[maxn];
    inline void coredge(int from,int to,lli len) {
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,lli len) {
        coredge(a,b,len) , coredge(b,a,len);
    }
    inline void dfs(int pos,int fa,const int &fs,lli& su,lli& mx,lli& mi) {
        siz[pos] = sel[pos] , f[pos] = sel[pos] ? 0 : -inf , g[pos] = sel[pos] ? 0 : inf;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
            dfs(t[at],pos,fs,su,mx,mi) , su += l[at] * siz[t[at]] * ( fs - siz[t[at]] ) , siz[pos] += siz[t[at]];
            mx = std::max( mx , f[pos] + f[t[at]] + l[at] ) , f[pos] = std::max( f[pos] , f[t[at]] + l[at] );
            mi = std::min( mi , g[pos] + g[t[at]] + l[at] ) , g[pos] = std::min( g[pos] , g[t[at]] + l[at] );
        }
        s[pos] = sel[pos] = 0;
    }
}

inline bool cmp(int x,int y) {
    return dfn[x] < dfn[y];
}
inline void solve_case() {
    static int in[maxn],stk[maxn],m,top,root;
    static lli su,mx,mi;
    scanf("%d",&m) , top = 0 , VirtualTree::cnt = 0;
    for(int i=1;i<=m;i++) scanf("%d",in+i) , sel[in[i]] = 1;
    std::sort(in+1,in+1+m,cmp);
    for(int i=1,p,l;i<=m;i++) {
        p = in[i];
        if( !top ) stk[++top] = p;
        else {
            l = lca(p,stk[top]);
            while( dfn[l] < dfn[stk[top]] ) {
                if( top == 1 || dfn[stk[top-1]] <= dfn[l] ) {
                    VirtualTree::addedge(l,stk[top],dep[stk[top]]-dep[l]) , --top;
                    if( stk[top] != l ) stk[++top] = l;
                    break;
                }
                VirtualTree::addedge(stk[top-1],stk[top],dep[stk[top]]-dep[stk[top-1]]) , --top;
            }
            stk[++top] = p;
        }
    }
    while( top > 1 ) VirtualTree::addedge(stk[top-1],stk[top],dep[stk[top]]-dep[stk[top-1]]) , --top;
    root = stk[top] , su = 0 , mx = -inf , mi = inf;
    VirtualTree::dfs(root,-1,m,su,mx,mi) , printf("%lld %lld %lld\n",su,mi,mx);
}

int main() {
    static int n,m;
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , Tree::addedge(a,b);
    Tree::pre(1) , Tree::dfs(1) , scanf("%d",&m);
    while(m--) solve_case();
    return 0;
}
