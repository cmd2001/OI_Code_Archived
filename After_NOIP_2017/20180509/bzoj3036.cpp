#include<cstdio>
const int maxn=1e5+1e2,maxe=2e5+1e2;

int s[maxn],t[maxe],nxt[maxe],l[maxe],deg[maxn];
double f[maxn];
double vis[maxn];

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    if(vis[pos]) return;
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) dfs(t[at]) , f[pos] += f[t[at]] + l[at];
    if( deg[pos] ) f[pos] /= deg[pos];
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , ++deg[a];
    dfs(1) , printf("%0.2lf\n",f[1]);
    return 0;
}
