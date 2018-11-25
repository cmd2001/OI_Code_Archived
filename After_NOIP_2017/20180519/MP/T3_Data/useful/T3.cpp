#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define bool unsigned char
using namespace std;
const int maxn=5e2+1e1;

std::vector<int> in[maxn];
int fa[maxn];
bool vis[maxn];

inline bool dfs(int pos) {
    vis[pos] = 1 , std::random_shuffle(in[pos].begin(),in[pos].end());
    for(auto i:in[pos]) if( !fa[i] ) return fa[pos] = i , fa[i] = pos , 1;
    for(auto i:in[pos]) {
        const int t = fa[i];
        if( vis[t] ) continue;
        fa[i] = pos , fa[pos] = i , fa[t] = 0;
        if( dfs(t) ) return 1;
        fa[i] = t , fa[t] = i , fa[pos] = 0;
    }
    return 0;
}

int main() {
    static int n,m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , in[a].push_back(b) , in[b].push_back(a);
    for(int T=10;T;T--) for(int i=1;i<=n;i++) if( !fa[i] ) memset(vis,0,sizeof(vis)) , dfs(i);
    for(int i=1;i<=n;i++) if(fa[i]) ++ans;
    printf("%d\n",n-(ans>>1));
    return 0;
}
