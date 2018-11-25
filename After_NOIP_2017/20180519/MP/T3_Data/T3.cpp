#include<bits/stdc++.h>
using namespace std;
const int maxn=5e2+1e2;

int in[maxn][maxn],vis[maxn],fa[maxn],n;

inline bool dfs(int pos) {
    for(int i=1;i<=n;i++) if( in[pos][i] && !vis[i] ) {
        vis[i] = 1;
        if( !fa[i] || dfs(fa[i]) ) return fa[i] = pos , 1;
    }
    return 0;
}

int main() {
    static int m,pir;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , in[a][b] = in[b][a] = 1;
    for(int i=1;i<=n;i++) memset(vis,0,sizeof(vis)) , pir += dfs(i);
    printf("%d\n",n-(pir>>1));
    return 0;
}