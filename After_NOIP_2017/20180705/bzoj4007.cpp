#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e3+1e2;

int w[maxn][13],g[maxn][13],f[maxn][maxn];
int n,m,ans;

inline void dfs(int pos,int sta,int dep) { // 1 means war .
    memset(f[pos],0,sizeof(f[pos]));
    if( dep == n ) {
        for(int i=1;i<n;i++) {
            if( sta & ( 1 << ( i - 1 ) ) ) f[pos][1] += w[pos][i];
            else f[pos][0] += g[pos][i];
        }
        return;
    }
    const int lson = pos << 1 , rson = pos << 1 | 1 , fs = 1 << ( n - dep - 1 ) ;
    dfs(lson,sta<<1,dep+1) , dfs(rson,sta<<1,dep+1);
    for(int i=0;i<=fs;i++) for(int j=0;j<=fs;j++) f[pos][i+j] = max( f[pos][i+j] , f[lson][i] + f[rson][j] );
    dfs(lson,sta<<1|1,dep+1) , dfs(rson,sta<<1|1,dep+1);
    for(int i=0;i<=fs;i++) for(int j=0;j<=fs;j++) f[pos][i+j] = max( f[pos][i+j] , f[lson][i] + f[rson][j] );
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=(1<<(n-1));i<(1<<n);i++) for(int j=1;j<n;j++) scanf("%d",w[i]+j);
    for(int i=(1<<(n-1));i<(1<<n);i++) for(int j=1;j<n;j++) scanf("%d",g[i]+j);
    dfs(1,0,1); for(int i=0;i<=m;i++) ans = max( ans , f[1][i] );
    printf("%d\n",ans);
    return 0;
}
