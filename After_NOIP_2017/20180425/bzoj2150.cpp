#include<cstdio>
#include<cstring>
#define bool unsigned char
const int maxn=2.5e3+1e2,maxe=1e4+1e2,maxl=75;

char in[maxl][maxl];
int id[maxl][maxl];
int s[maxn],t[maxe<<3],nxt[maxe<<3];
int fa[maxn];
bool vis[maxn];
int n,m,r,c,ful;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool dfs(int pos) {
    for(int at=s[pos];at;at=nxt[at]) if( !vis[t[at]] ) {
        vis[t[at]] = 1;
        if( !fa[t[at]] || dfs(fa[t[at]]) ) return fa[t[at]] = pos , 1;
    }
    return 0;
}
inline int pir() {
    int ret = 0;
    for(int i=1;i<=ful;i++) memset(vis,0,sizeof(vis)) , ret += dfs(i);
    return ret;
}

int main() {
    scanf("%d%d%d%d",&n,&m,&r,&c);
    for(int i=1;i<=n;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=m;j++) if( in[i][j] == '.' ) id[i][j] = ++ful;
    }
    for(int i=1;i<=n;i++)
        for(int j=1,tx,ty;j<=m;j++)
            if( id[i][j] ) {
                if( i + r <= n && j + c <= m && id[i+r][j+c] ) addedge(id[i][j],id[i+r][j+c]);
                if( i + c <= n && j + r <= m && id[i+c][j+r] ) addedge(id[i][j],id[i+c][j+r]);
                if( i + r <= n && j - c >= 1 && id[i+r][j-c] ) addedge(id[i][j],id[i+r][j-c]);
                if( i + c <= n && j - r >= 1 && id[i+c][j-r] ) addedge(id[i][j],id[i+c][j-r]);
            }
    printf("%d\n",ful-pir());
    return 0;
}

