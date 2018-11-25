#include<cstdio>
#include<algorithm>
typedef long double ldb;
const int maxn=33;

ldb f[maxn][maxn],in[maxn],su[maxn],k,c,all;
bool vis[maxn][maxn];

inline ldb dfs(int l,int r) {
    if( l > r ) return 0;
    if( vis[l][r] ) return f[l][r];
    vis[l][r] = 1 , f[l][r] = 1e18;
    for(int i=l;i<=r;i++) f[l][r] = std::min( f[l][r] , dfs(l,i-1) + dfs(i+1,r) );
    return f[l][r] += ( su[r] - su[l-1] ) * k; 
}

int main() {
    static int n;
    scanf("%d%Lf%Lf",&n,&k,&c);
    for(int i=1;i<=n;i++) scanf("%Lf",in+i) , all += in[i];
    for(int i=1;i<=n;i++) su[i] = su[i-1] + ( in[i] /= all );
    printf("%0.3Lf\n",dfs(1,n)+c);
    return 0;    
}

