#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
const int maxn=5e3+1e2;
const short inf=0x3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
short f[maxn][maxn],g[maxn][maxn],can[maxn][maxn],tf[maxn],tg[maxn];
int siz[maxn],in[maxn],n;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    for(int i=0;i<=n;i++) f[pos][i] = inf , g[pos][i] = -inf;
    siz[pos] = f[pos][in[pos]] = g[pos][in[pos]] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos); for(int i=0;i<=siz[pos]+siz[t[at]];i++) tf[i] = inf , tg[i] = -inf;
        for(int i=0;i<=siz[pos];i++) for(int j=0;j<=siz[t[at]];j++) tf[i+j] = min( (int)tf[i+j] , f[pos][i] + f[t[at]][j] ) , tg[i+j] = max( (int)tg[i+j] , g[pos][i] + g[t[at]][j] );
        siz[pos] += siz[t[at]]; for(int i=0;i<=siz[pos];i++) f[pos][i] = min( f[pos][i] , tf[i] ) , g[pos][i] = max( g[pos][i] , tg[i] );
    }
    for(int i=0;i<=siz[pos];i++) if( f[pos][i] != inf && g[pos][i] != -inf ) ++can[i][f[pos][i]] , --can[i][g[pos][i]+1];
}
inline void getsum() {
    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) can[i][j] += can[i][j-1];
}

inline void reset() {
    memset(can,0,sizeof(can)) , memset(s,0,sizeof(s)) , cnt = 1;
}

int main() {
    static int T,q,x,y;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&q) , reset();
        for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        dfs(1,-1) , getsum();
        while(q--) scanf("%d%d",&x,&y) , puts(can[y][x]?"YES":"NO");
        putchar('\n');
    }
    return 0;
}
