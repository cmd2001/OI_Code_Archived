#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=5e3+1e2,maxq=1e4+1e2;

int s[maxn],t[maxq<<2],nxt[maxq<<3];
signed char ine[maxn][maxn],vis[maxn];
int es[maxn][maxn];
int ot[maxq],ox[maxq],oy[maxq];
int fa[maxn];
int n,m,ans;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline int findfa(int x) {
    return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}
inline void merge(int x,int y) {
    x = findfa(x) , y = findfa(y);
    if( x != y ) fa[y] = x;
}
inline void mine() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if( ine[i][j] == 1 )
                if( fa[i] != fa[j] ) merge(i,j);
}
inline void cov() {
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            if( !~ine[i][j] ) {
                int fi = findfa(i) , fj = findfa(j);
                if( fi != fj ) es[fi][fj]++ , es[fj][fi]++ , addedge(fi,fj) , addedge(fj,fi);
            }
    for(int i=1;i<=m;i++)
        if( ot[i] ) ox[i] = findfa(ox[i]) , oy[i] = findfa(oy[i]);
}
inline void dfs(int pos) {
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( es[pos][t[at]] && !vis[t[at]] )
            dfs(t[at]);
}
inline void preans() {
    for(int i=1;i<=n;i++)
        if( fa[i] == i && !vis[i] ) {
            ++ans;
            dfs(i);
        }
}
inline void calc_merge(int x,int y) {
    memset(vis,0,sizeof(vis));
    dfs(x) , ans -= !vis[y];
    ++es[x][y] , ++es[y][x];
}
inline void calc_cut(int x,int y) {
    memset(vis,0,sizeof(vis));
    --es[x][y] , --es[y][x];
    dfs(x) , ans += !vis[y];
}

int main() {
    static int p;
    static char o[10];
    scanf("%d%d",&n,&p);
    for(int i=1,a,b;i<=p;i++) {
        scanf("%d%d",&a,&b);
        ine[a][b] = ine[b][a] = 1;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++) {
        scanf("%s",o);
        if( *o != 'Q' ) {
            ot[i] = 1 + ( *o == 'D' ); // 1 means add , 2 means delete .
            scanf("%d%d",ox+i,oy+i);
            if( ot[i] == 2 && ine[ox[i]][oy[i]] ) ine[ox[i]][oy[i]] = ine[oy[i]][ox[i]] = -1; // this edge will be deleted .
        }
    }
    for(int i=1;i<=n;i++) fa[i] = i;
    mine() , cov() , preans();
    for(int i=1;i<=m;i++) {
        if( !ot[i] ) printf("%d\n",ans);
        else if( ot[i] == 1 ) calc_merge(ox[i],oy[i]);
        else if( ot[i] == 2 ) calc_cut(ox[i],oy[i]);
    }
    return 0;
}

