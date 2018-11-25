#include<cstdio>
#include<cstring>
#include<algorithm>
#define bool unsigned char
#define lli long long int
using namespace std;
const int maxn=2e2+1e1;

int s[maxn],t[maxn*maxn<<1],nxt[maxn*maxn<<1];
lli in[maxn][maxn];
lli mx[maxn],fa[maxn];
bool vis[maxn];

inline void addedge(int from,int to) {
    static int cnt = 0;
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

int main() {
    static int n,m;
    static lli ans;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            scanf("%lld",in[i]+j);
            if( in[i][j] ) ans += in[i][j] - 1;
            mx[i] = max( mx[i] , in[i][j] ) ,
            mx[j+n] = max( mx[j+n] , in[i][j] );
        }
    for(int i=1;i<=n+m;i++)
        if( mx[i] )
            ans -= mx[i] - 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( mx[i] && in[i][j] && mx[i] == mx[j+n] )
                addedge(i,j+n);
    for(int i=1;i<=n;i++) {
        memset(vis,0,sizeof(vis));
        if( mx[i] && dfs(i) ) {
            ans += mx[i] - 1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
