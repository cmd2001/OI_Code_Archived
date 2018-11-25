#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e1;

lli dis[maxn/10][maxn/10],c[maxn],t[maxn];
int in[maxn][maxn],fa[maxn];
int vis[maxn];
int n,m,ans,q;

inline void floyd() {
    for(int i=1;i<=n;i++)
        dis[i][i] = 0;
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j] = dis[j][i] = min( dis[i][j] , dis[i][k] + dis[k][j] );
}
inline bool dfs(int pos) {
    for(int i=1;i<=q;i++)
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
    for(int i=1;i<=q;i++) {
        memset(vis,0,sizeof(vis));
        ret += dfs(i);
    }
    return ret;
}

int main() {
    scanf("%d%d%d",&n,&m,&q);
    memset(dis,0x3f,sizeof(dis));
    for(int i=1,a,b,x;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&x);
        a++,b++;
        dis[a][b] = dis[b][a] = min( dis[a][b] , (lli)x );
    }
    for(int i=1;i<=q;i++)
        scanf("%lld%lld",c+i,t+i),
        c[i]++;
    
    floyd();
    /*for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++)
            debug<<dis[i][j]<<" ";
        debug<<endl;
    }*/
    for(int i=1;i<=q;i++)
        for(int j=1;j<=q;j++)
            if( i!=j && dis[c[i]][c[j]] <= t[j] - t[i] ) {
                //debug<<"i = "<<i<<"j = "<<j<<endl;
                in[i][j] = 1;
            }
    
    ans = getans();
    //debug<<"ans = "<<ans<<endl;
    ans = q - ans - 1;
    
    printf("%d\n",ans);
    
    return 0;
    
}