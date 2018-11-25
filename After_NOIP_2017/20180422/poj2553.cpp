#include<cstdio>
#include<algorithm>
const int maxn=5e4+1e2;

int s[maxn],t[maxn],nxt[maxn],fm[maxn],to[maxn],cnt;
int vis[maxn],ins[maxn],dfn[maxn],low[maxn],bel[maxn],deg[maxn],stk[maxn],dd,iid,top;
int ans[maxn],anslen,n,m;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    vis[pos] = ins[stk[++top]=pos] = 1 , low[pos] = dfn[pos] = ++dd;
    for(int at=s[pos];at;at=nxt[at])
        if( !vis[t[at]] ) dfs(t[at]) , low[pos] = std::min(low[pos],low[t[at]]);
        else if( ins[t[at]] ) low[pos] = std::min(low[pos],dfn[t[at]]);
    if( low[pos] == dfn[pos] ) {
        ++iid;
        do {
            const int x = stk[top--]; ins[x] = 0 , bel[x] = iid;
        } while( ins[pos] );
    }
}
inline void calans() {
    for(int i=1;i<=m;i++) if( bel[fm[i]] != bel[to[i]] ) ++deg[bel[fm[i]]];
    for(int i=1;i<=n;i++) if( !deg[bel[i]] ) ans[++anslen] = i;
    if( anslen ) std::sort(ans+1,ans+1+anslen);
}
inline void reset() {
    for(int i=1;i<=n;i++) s[i] = vis[i] = ins[i] = dfn[i] = low[i] = bel[i] = deg[i] = 0;
    anslen = dd = iid = top = cnt = 0;
}
int main() {
    while( scanf("%d",&n) == 1 && n ) {
        scanf("%d",&m) , reset();
        for(int i=1;i<=m;i++) scanf("%d%d",fm+i,to+i) , addedge(fm[i],to[i]);
        for(int i=1;i<=n;i++) if( !vis[i] ) dfs(i);
        calans(); for(int i=1;i<=anslen;i++) printf("%d%c",ans[i],i!=anslen?' ':'\n');
        if( !anslen ) putchar('\n');
    }
    return 0;
}
