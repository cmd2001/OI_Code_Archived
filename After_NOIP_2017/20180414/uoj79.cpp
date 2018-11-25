#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=5e2+1e1;

vector<int> in[maxn];
int fa[maxn];
bool vis[maxn],used[maxn];

inline bool dfs(int pos) {
    vis[pos] = 1 , random_shuffle(in[pos].begin(),in[pos].end());
    for(unsigned i=0;i<in[pos].size();i++)
        if( !used[in[pos][i]] ) {
            used[pos] = used[in[pos][i]] = 1 ,
            fa[pos] = in[pos][i] , fa[in[pos][i]] = pos;
            return 1;
        }
    for(unsigned i=0;i<in[pos].size();i++) {
        const int tar = in[pos][i] , mth = fa[tar];
        if( vis[mth] ) continue;
        used[pos] = 1 , fa[tar] = pos , fa[pos] = tar , used[mth] = fa[mth] = 0;
        if( dfs(mth) ) return 1;
        used[mth] = 1 , fa[tar] = mth , fa[mth] = tar , used[pos] = fa[pos] = 0;
    }
    return 0;
}

int main() {
    static int n,m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , in[a].push_back(b) , in[b].push_back(a);
    for(int T=1;T<=10;T++) for(int i=1;i<=n;i++) if( !used[i] ) memset(vis,0,sizeof(vis)) , dfs(i);
    for(int i=1;i<=n;i++) ans += used[i];
    printf("%d\n",ans>>1);
    for(int i=1;i<=n;i++) printf("%d%c",fa[i],i!=n?' ':'\n');
    return 0;
}
