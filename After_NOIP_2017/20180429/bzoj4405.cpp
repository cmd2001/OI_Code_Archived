#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define bool unsigned char
const int maxn=6e2+1e1;

std::vector<int> in[maxn];
int fa[maxn];
bool vis[maxn];
int n,m;

inline void doubledge(int a,int b) {
    in[a].push_back(b) , in[b].push_back(a);
}
inline bool dfs(int pos) {
    vis[pos] = 1 , std::random_shuffle(in[pos].begin(),in[pos].end());
    for(unsigned i=0;i<in[pos].size();i++) if( !fa[in[pos][i]] ) return fa[pos] = in[pos][i] , fa[in[pos][i]] = pos , 1;
    for(unsigned i=0;i<in[pos].size();i++) {
        const int tar = in[pos][i] , mth = fa[tar];
        if( vis[mth] ) continue;
        fa[tar] = pos , fa[pos] = tar , fa[mth] = 0;
        if( dfs(mth) ) return 1;
        fa[mth] = tar , fa[tar] = mth , fa[pos] = 0;
    }
    return 0;
}

inline int cov(int x,int tpe) {
    return 3 * --x + tpe + n;
}
inline void reset() {
    memset(fa,0,sizeof(fa));
    for(int i=1;i<=n+m*3;i++) in[i].clear();
}

int main() {
    static int T,e,full,ans;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d",&n,&m,&e) , full = n + m * 3 , reset() , ans = 0;
        for(int i=1,a,b;i<=e;i++) {
            scanf("%d%d",&a,&b);
            for(int j=1;j<=3;j++) doubledge(a,cov(b,j));
        }
        for(int i=1;i<=m;i++) doubledge(cov(i,1),cov(i,2)) , doubledge(cov(i,2),cov(i,3));
        for(int t=1;t<=10;t++) for(int i=1;i<=full;i++) if( !fa[i] ) memset(vis,0,sizeof(vis)) , dfs(i);
        for(int i=1;i<=full;i++) if( fa[i] ) ++ans;
        ans >>= 1 , ans -= n;
        printf("%d\n",ans);
        //for(int i=1;i<=n;i++) printf("%d%c",(fa[i]-n-1)/3+1,i!=n?' ':'\n');
    }
    return 0;
}

