#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=11,maxs=1<<10;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
const int inf=0x3f3f3f3f;

struct Node {
    int x,y,sta;
}from[maxs][maxn][maxn];
struct Point {
    int x,y;
};
int f[maxs][maxn][maxn],in[maxn][maxn],vis[maxn][maxn];
bool inq[maxn][maxn];
int n,m,full;

inline void spfa(int sta,int dis[maxn][maxn],Node from[maxn][maxn]) {
    queue<Point> q;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) q.push((Point){i,j}) , inq[i][j] = 1;
    while( q.size() ) {
        const int x = q.front().x , y = q.front().y; q.pop() , inq[x][y] = 0;
        for(int k=0;k<4;k++) {
            const int tx = x + dx[k] , ty = y + dy[k];
            if( 0 < tx && tx <=  n && 0 < ty && ty <= m ) {
                if( dis[tx][ty] > dis[x][y] + in[tx][ty] ) {
                    dis[tx][ty] = dis[x][y] + in[tx][ty] , from[tx][ty] = (Node){x,y,sta};
                    if( !inq[tx][ty] ) q.push((Point){tx,ty}) , inq[tx][ty] = 1;
                }
            }
        }
    }
}
inline void dp() {
    for(int sta=1;sta<=full;sta++) {
        for(int ss=sta&(sta-1);ss;ss=sta&(ss-1))
            for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
                if( f[sta][i][j] > f[ss][i][j] + f[sta^ss][i][j] - in[i][j] ) {
                    f[sta][i][j] = f[ss][i][j] + f[sta^ss][i][j] - in[i][j] , from[sta][i][j] = (Node){i,j,ss};
                }
        spfa(sta,f[sta],from[sta]);
    }
}
inline void init() {
    static int sum;
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( !in[i][j] ) f[1<<(sum++)][i][j] = 0;
    full = ( 1 << sum ) - 1;
}
inline void dfs(int x,int y,int sta) {
    vis[x][y] = 1;
    Node fr = from[sta][x][y];
    if( !fr.sta ) return;
    dfs(fr.x,fr.y,fr.sta);
    if( fr.x == x && fr.y == y ) dfs(fr.x,fr.y,sta^fr.sta);
}
inline void printway() {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if( !in[i][j] ) putchar('x');
            else if( vis[i][j] ) putchar('o');
            else putchar('_');
        }
        putchar('\n');
    }
}
inline void getans() {
    static int x,y;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( !in[i][j] ) { x = i , y = j; break; }
    printf("%d\n",f[full][x][y]);
    dfs(x,y,full);
    printway();
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",in[i]+j);
    init();
    dp();
    getans();
    return 0;
}
