#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=2e2+1e1,maxm=4e4+1e2;

struct Node {
    int a,b;
    friend bool operator < (const Node &a,const Node &b) {
        return a.b > b.b;
    }
}ns[maxn];
int f[maxn][maxm],sum[maxn],n,ans;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&ns[i].a,&ns[i].b);
    std::sort(ns+1,ns+1+n);
    for(int i=1;i<=n;i++) sum[i] = sum[i-1] + ns[i].a;
    memset(f,0x3f,sizeof(f)) , ans = **f , **f = 0;
    for(int i=1;i<=n;i++) {
        for(int j=ns[i].a;j<=sum[i];j++) f[i][j] = std::min( f[i][j] , std::max( f[i-1][j-ns[i].a] , j + ns[i].b) );
        for(int j=0;j<=sum[i];j++) f[i][j] = std::min( f[i][j] , std::max( f[i-1][j] , sum[i] - j + ns[i].b ) );
    }
    for(int i=0;i<=sum[n];i++) ans = std::min( ans , f[n][i] );
    printf("%d\n",ans);
    return 0;
}
