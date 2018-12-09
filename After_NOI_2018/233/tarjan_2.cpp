#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 2e4+1e2, maxe = 1e5+1e2;

int s[maxn],t[maxe<<1],nxt[maxe<<1];
int dfn[maxn],low[maxn],dd;
int ans[maxn],cnt;

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to, nxt[cnt] = s[from], s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b), coredge(b,a);
}
inline void dfs(int pos,bool isroot) {
    low[pos] = dfn[pos] = ++dd;
    int su = 0;
    for(int at=s[pos];at;at=nxt[at]) {
        if(!dfn[t[at]]) {
            dfs(t[at],0), low[pos] = min(low[pos],low[t[at]]);
            if(low[t[at]] >= dfn[pos] && !isroot) ans[++cnt] = pos;
            else if(isroot) ++su;
        } else low[pos] = min(low[pos],dfn[t[at]]);
    }
    if(isroot && su > 1) ans[++cnt] = pos;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b), addedge(a,b);
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,1);
    if(!cnt) return puts("0"), 0;
    sort(ans+1,ans+1+cnt), cnt = unique(ans+1,ans+1+cnt) - ans - 1;
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++) printf("%d%c",ans[i],i!=cnt?' ':'\n');
    return 0;
}

