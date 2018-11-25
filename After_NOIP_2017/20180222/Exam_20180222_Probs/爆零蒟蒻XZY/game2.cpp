#include<bits/stdc++.h>
using namespace std;
const int maxn=2e2+1e1;

int bakfa[maxn];
int in[maxn][maxn],fa[maxn],vis[maxn],used[maxn];
int ringed[maxn];
int n;

inline bool dfs(int pos) {
    if( used[pos] = 2 ) return 1;
    for(int i=1;i<=n;i++)
        if( used[i]!=1 && in[pos][i] && !vis[i] ) {
            vis[i] = 1;
            if( !fa[i] || dfs(fa[i]) ) {
                fa[i] = pos;
                return 1;
            }
        }
    return 0;
}
inline int ringsiz(int pos,int siz) {
    if( ringed[pos] ) return siz;
    ringed[pos] = 1;
    return ringsiz(fa[pos],siz+1);
}
inline int make() {
    for(itn i=1;i<=n;i++) {
    }
}
