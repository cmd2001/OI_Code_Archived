#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn = 1e4 + 1e2, maxe = 1e5 + 1e2;

int a[maxe],b[maxe],in[maxn],siz,ans;

struct OriginalGraph {
    int s[maxn],t[maxe],nxt[maxe],dfn[maxn],low[maxn],bel[maxn];
    int stk[maxn],ins[maxn],top;
    inline void addedge(int from,int to) {
        static int cnt;
        t[++cnt] = to, nxt[cnt] = s[from], s[from] = cnt;
    }
    inline void dfs(int pos) {
        static int dd;
        low[pos] = dfn[pos] = ++dd, ins[stk[++top]=pos] =1;
        for(int at=s[pos];at;at=nxt[at]) {
            if(!dfn[t[at]]) dfs(t[at]), low[pos] = min(low[pos],low[t[at]]);
            else if(ins[t[at]]) low[pos] = min(low[pos],dfn[t[at]]);
        }
        if(low[pos] >= dfn[pos]) {
            ++siz;
            do {
                const int x = stk[top--];
                ins[x] = 0, bel[x] = siz;
            } while(ins[pos]);
        }
    }
}og;

struct NewGraph {
    int s[maxn],t[maxe],nxt[maxe],deg[maxe],val[maxn],f[maxn];
    inline void addedge(int from,int to) {
        static int cnt;
        t[++cnt] = to, nxt[cnt] = s[from], s[from] = cnt, ++deg[to];
    }
    inline void topo() {
        queue<int> q;
        for(int i=1;i<=siz;i++) if(!deg[i]) q.push(i);
        while(q.size()) {
            const int pos = q.front(); q.pop();
            f[pos] += val[pos], ans = max(ans,f[pos]);
            for(int at=s[pos];at;at=nxt[at]) {
                f[t[at]] = max(f[pos],f[t[at]]);
                if(!--deg[t[at]]) q.push(t[at]);
            }
        }
    }
}ng;

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++) scanf("%d%d",a+i,b+i), og.addedge(a[i],b[i]);
    for(int i=1;i<=n;i++) if(!og.dfn[i]) og.dfs(i);
    for(int i=1;i<=n;i++) ng.val[og.bel[i]] += in[i];
    for(int i=1;i<=m;i++) if(og.bel[a[i]] != og.bel[b[i]]) ng.addedge(og.bel[a[i]],og.bel[b[i]]);
    ng.topo(), printf("%d\n",ans);
    return 0;
}

