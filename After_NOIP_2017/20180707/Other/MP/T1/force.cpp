#include<bits/stdc++.h>
using namespace std;
const int maxn=4e4+1e2,maxe=3e6+1e2;

int xs[maxn],ys[maxn];
int s[maxn],t[maxe<<1],nxt[maxe<<1],fa[maxn];
bool vis[maxn];

int n,m;

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool dfs(int pos) {
    for(int at=s[pos];at;at=nxt[at]) if( !vis[t[at]] ) {
        vis[t[at]] = 1;
        if( !fa[t[at]] || dfs(fa[t[at]]) ) return fa[t[at]] = pos , 1;
    }
    return 0;
}
inline int calc() {
    int ret = 0;
    for(int i=n+1;i<=n+m;i++) memset(vis,0,sizeof(vis)) , ret += dfs(i);
    return ret;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",xs+i,ys+i);
    for(int i=1,x,y,d;i<=m;i++) {
        scanf("%d%d%d",&x,&y,&d);
        for(int j=1;j<=n;j++) if( abs(x-xs[j]) + abs(y-ys[j]) <= d ) addedge(n+i,j);
    }
    printf("%d\n",calc());
    return 0;
}


