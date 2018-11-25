#pragma GCC optimize("Ofast","no-stack-protector")
//#pragma GCC target("avx2")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=4e3+1e2;

int lson[maxn],rson[maxn],c[maxn],siz[maxn];
lli f[maxn][maxn];
bool vis[maxn];

inline void dfs(int pos) {
    if( !lson[pos] && !rson[pos] ) { // a leaf node .
        f[pos][0] = 0 , f[pos][1] = c[pos] , siz[pos] = 1;
        return;
    }
    dfs(lson[pos]) , dfs(rson[pos]) , memset(f[pos],0x3f,(siz[lson[pos]]+siz[rson[pos]]+1)<<3);
    for(int i=0;i<=siz[lson[pos]];i++) for(int j=0;j<=siz[rson[pos]];j++) f[pos][i+j] = std::min( f[pos][i+j] , f[lson[pos]][i] + f[rson[pos]][j] + (lli) ( i ^ j ) * c[pos] );
    siz[pos] = siz[lson[pos]] + siz[rson[pos]];
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int t,n,root;
    freopen("assist.in","r",stdin);
    freopen("assist.out","w",stdout);
    t = getint();
    while(t--) {
        n = getint() , memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++) vis[lson[i] = getint()] = 1 , vis[rson[i] = getint()] = 1;
        for(int i=1;i<=n;i++) c[i] = getint();
        for(int i=1;i<=n;i++) if( !vis[i] ) root = i;
        dfs(root);
        for(int i=1;i<=siz[root];i++) printf("%lld%c",f[root][i],i!=siz[root]?' ':'\n');
    }
    fclose(stdout);
    return 0;
}
