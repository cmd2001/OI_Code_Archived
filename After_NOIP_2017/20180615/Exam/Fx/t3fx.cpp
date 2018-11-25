#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=26,maxs=1<<5;
const int inf=0x3f3f3f3f;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

struct Node{int x,y;};
int a[maxn][maxn],b[maxn][maxn],fakea[maxn][maxn];
int f[maxs][maxn][maxn];
int n,m,k,fs,ans;

inline void spfa(int dis[maxn][maxn]) {
    static bool inq[maxn][maxn];
    queue<Node> q;
    #define legal(x,y) (0<x&&x<=n&&0<y&&y<=m)
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( dis[i][j] < ans ) q.push((Node){i,j});
    while( q.size() ) {
        const int x = q.front().x , y = q.front().y; q.pop() , inq[x][y] = 0;
        for(int i=0;i<4;i++) {
            const int tx = x + dx[i] , ty = y + dy[i];
            if( legal(tx,ty) && ~fakea[tx][ty]  && dis[tx][ty] > dis[x][y] + b[tx][ty] ) {
                dis[tx][ty] = dis[x][y] + b[tx][ty];
                if( dis[tx][ty] >= ans ) { dis[tx][ty] = inf; continue; }
                if( !inq[tx][ty] ) q.push((Node){tx,ty});
            }
        }
    }
}
inline int solve() {
    int ret = inf;
    memset(f,0x3f,sizeof(f)) , fs = 1 << k;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( ~fakea[i][j] ) f[1<<fakea[i][j]][i][j] = b[i][j];
    for(int i=0;i<fs;i++) {
        for(int j=i;j;j=(j-1)&i) for(int x=1;x<=n;x++) for(int y=1;y<=m;y++) if( ~fakea[i][j] )
            f[i][x][y] = min( f[i][x][y] , f[j][x][y] + f[i^j][x][y] - b[x][y] );
        spfa(f[i]);
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ret = min( ret , f[fs-1][i][j] );
    return ret;
}
inline void gen() {
    static int ls[maxn*maxn];
    for(int i=0;i<=n*m;i++) ls[i] = rand() % k;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) fakea[i][j] = (~a[i][j]) ? ls[a[i][j]] : -1;
}
inline void getans() {
    for(int i=1;i<=150;i++) gen() , ans = min( ans , solve() );
}

inline void init() {
    static const char seed[] = "KurenaiKisaragi";
    int su = 0 , li = strlen(seed);
    for(int i=0;i<li;i++) su += seed[i];
    srand(su);
}

int main() {
    static int T;
    scanf("%d",&T) , init();
    while(T--) {
        scanf("%d%d%d",&n,&m,&k) , ans = inf;
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",a[i]+j);
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",b[i]+j);
        getans() , printf("%d\n",ans==inf?-1:ans);
    }
    return 0;
}
