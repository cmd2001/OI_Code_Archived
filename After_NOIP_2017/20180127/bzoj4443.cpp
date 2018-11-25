#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=5e2+1e2;

int s[maxn],t[maxn*maxn<<1],nxt[maxn*maxn<<1],cnt;
int in[maxn][maxn];
int fa[maxn];
bool vis[maxn];
int n,m,k;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool dfs(int pos) {
    for(int at=s[pos];at;at=nxt[at])
        if( !vis[t[at]] ) {
            vis[t[at]] = 1;
            if( !fa[t[at]] || dfs(fa[t[at]]) ) {
                fa[t[at]] = pos;
                return 1;
            }
        }
    return 0;
}
inline int pir() {
    int ret = 0;
    memset(fa,0,sizeof(fa));
    for(int i=1;i<=n;i++) {
        memset(vis,0,sizeof(vis));
        ret += dfs(i);
    }
    return ret;
}
inline bool check(int x) {
    memset(s,0,sizeof(s)) , cnt = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] <= x )
                addedge(i,j+n);
    return pir() >= n - k + 1;
}
inline int bin() {
    int l = 0 , r = 1e9 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( check(mid) ) r = mid;
        else l = mid;
    }
    return r;
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",in[i]+j);
    printf("%d\n",bin());
    return 0;
}
