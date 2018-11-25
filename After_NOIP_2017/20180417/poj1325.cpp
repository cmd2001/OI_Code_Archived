#include<cstdio>
#include<cstring>
#define bool unsigned char
const int maxn=1e2+1e1;

bool in[maxn][maxn],vis[maxn];
int fa[maxn],n,m;

inline bool dfs(int pos) {
    for(int i=1;i<=m;i++)
        if( in[pos][i] && !vis[i] ) {
            vis[i] = 1;
            if( !fa[i] || dfs(fa[i]) ) return fa[i] = pos , 1;
        }
    return 0;
}
inline int pir() {
    int ret = 0;
    for(int i=1;i<=n;i++) memset(vis,0,sizeof(vis)) , ret += dfs(i);
    return ret;
}

int main() {
    static int k,a,b;
    while( scanf("%d",&n) == 1 && n ) {
        scanf("%d%d",&m,&k) , memset(in,0,sizeof(in)) , memset(fa,0,sizeof(fa));
        while(k--) scanf("%*d%d%d",&a,&b) , in[a][b] = 1;
        printf("%d\n",pir());
    }
    return 0;
}
