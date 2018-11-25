#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e2+1e1;

int in[maxn][maxn];
int fa[maxn],vis[maxn];
int n;

inline void floyd() {
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                in[i][j] |= ( in[i][k] && in[k][j] );
}
inline bool dfs(int pos) {
    for(int i=1;i<=n;i++)
        if( in[pos][i] && !vis[i] ) {
            vis[i] = 1;
            if( !fa[i] || dfs(fa[i]) ) {
                fa[i] = pos;
                return 1;
            }
        }
    return 0;
}
inline int getans() {
    int ret = 0;
    for(int i=1;i<=n;i++) {
        memset(vis,0,sizeof(vis));
        //vis[i] = 1;
        ret += dfs(i);
    }
    return ret;
}

int main() {
    static int m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        in[a][b] = 1;
    }
    
    floyd();
    
    ans = n - getans();
    
    printf("%d\n",ans);
    
    return 0;
}