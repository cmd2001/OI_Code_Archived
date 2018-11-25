#include<cstdio>
#include<vector>
const int maxn=2e5+1e2;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        return x == y ? 0 : fa[x] = y;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

std::vector<int> es[maxn];
int in[maxn],ban[maxn],ans[maxn],now;

int main() {
    static int n,m,a,b;
    scanf("%d%d",&n,&m) , ufs.init(n);
    for(int i=1;i<=m;i++) scanf("%d%d",&a,&b) , es[a].push_back(b) , es[b].push_back(a);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , ban[i] = 1;
    for(int i=n,t;i;i--) {
        ++now , ban[t=in[i]] = 0;
        for(unsigned j=0;j<es[t].size();j++) if( !ban[es[t][j]] ) now -= ufs.merge(t,es[t][j]);
        ans[i] = ( now == 1 );
    }
    for(int i=1;i<=n;i++) puts(ans[i]?"YES":"NO");
    return 0;
}
