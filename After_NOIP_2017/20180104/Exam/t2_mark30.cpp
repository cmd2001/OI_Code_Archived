#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxd=30;

char in[maxn];
int g[maxd][maxd],can[maxd][maxd],vis[maxd],app[maxd];
int mxl,n,k,len;

inline void floyd() {
    for(int k=1;k<=26;k++)
        for(int i=1;i<=26;i++)
            for(int j=1;j<=26;j++)
                can[i][j] |= ( can[i][k] & can[k][j] );
}

inline bool judgeinf() {
    floyd();
    for(int i=1;i<=26;i++)
        if( can[i][i] )
            return 1;
    return 0;
}

inline void dfs(int pos,int dep) {
    vis[pos] = 1;
    mxl = max( mxl , dep );
    for(int i=1;i<=26;i++)
        if( g[pos][i] && !vis[i] )
            dfs(i,dep+1);
    vis[pos] = 0;
}

inline int cov(int x) {
    return x - 'a' + 1;
}
inline void init() {
    memset(g,0,sizeof(g));
    memset(can,0,sizeof(can));
    memset(app,0,sizeof(app));
    mxl = 0;
}

int main() {
    while( scanf("%d%d",&n,&k) == 2 ) {
        if( k != 2 ) {
            puts("INF");
            continue;
        }
        init();
        for(int i=1;i<=n;i++) {
            scanf("%s",in+1);
            len = strlen(in+1);
            for(int i=1;i<=len;i++)
                app[cov(in[i])] = 1;
            for(int i=1;i<len;i++) {
                can[cov(in[i])][cov(in[i+1])] = g[cov(in[i])][cov(in[i+1])] = 1;
            }
        }
        if( judgeinf() )
            puts("INF");
        else {
            for(int i=1;i<=26;i++)
                if( app[i] )
                    dfs(i,1);
            printf("%d\n",mxl);
        }
    }
    return 0;
}