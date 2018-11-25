#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=5e2+1e1;

std::vector<int> in[maxn];
int fa[maxn];
bool vis[maxn];

inline bool dfs(int pos) {
    vis[pos] = 1 , std::random_shuffle(in[pos].begin(),in[pos].end());
    for(unsigned i=0;i<in[pos].size();i++) if( !fa[in[pos][i]] ) return fa[in[pos][i]] = pos , fa[pos] = in[pos][i] , 1;
    for(unsigned i=0;i<in[pos].size();i++) {
        const int t = in[pos][i] , m = fa[in[pos][i]];
        if( vis[m] ) continue;
        fa[pos] = t , fa[t] = pos , fa[m] = 0;
        if( dfs(m) ) return 1;
        fa[m] = t , fa[t] = m , fa[pos] = 0;
    }
    return 0;
}

int main() {
    static int n,m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , in[a].push_back(b) , in[b].push_back(a);
    for(int t=1;t<=10;t++) for(int i=1;i<=n;i++) if( !fa[i] ) memset(vis,0,sizeof(vis)) , dfs(i);
    for(int i=1;i<=n;i++) ans += (bool) fa[i];
    printf("%d\n",ans>>1);
    for(int i=1;i<=n;i++) printf("%d%c",fa[i],i!=n?' ':'\n');
    return 0;
}
