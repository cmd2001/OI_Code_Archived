#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
using namespace std;
const int maxn=5e2+1e1,maxt=10;
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
const int inf = 0x3f3f3f3f;

//enum DIRECTION{UP,RIGHT,DOWN,LEFT};

struct pii{short l,r;};
pii tar[maxn][maxn][4];
bool vis[maxn][maxn][4],ins[maxn][maxn][4];
char in[maxn][maxn];
int n,m,k,ans;

#define legal(x,y) ( 0 < x && x <= n && 0 < y && y <= m && in[x][y] != 'x' )
inline pii dfs(int x,int y,int dir) { // it may stop at rotating point .
    if( ins[x][y][dir] ) return (pii){-1,-1};
    if( vis[x][y][dir] ) return tar[x][y][dir];
    int dd = dir; ins[x][y][dir] = vis[x][y][dir] = 1;
    if( in[x][y] != '.' ) dd = ( dir + 'D' - in[x][y]) & 3;
    const int tx = x + dx[dd] , ty = y + dy[dd];
    if( !legal(tx,ty) ) tar[x][y][dir] = (pii){x,y};
    else tar[x][y][dir] = dfs(tx,ty,dd);
    return ins[x][y][dir] = 0 , tar[x][y][dir];
}
#undef legal

int f[maxt][maxt][maxn][maxn];

struct SortNode {
    short x,y; int dis;
    friend bool operator < (const SortNode &a,const SortNode &b) {
        return a.dis < b.dis;
    }
}sns[maxn*maxn];
struct QueNode { short x,y; };

inline void spfa(int dis[maxn][maxn]) {
    int cnt = 0;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( dis[i][j] != inf ) sns[++cnt] = (SortNode){i,j,dis[i][j]};
    sort(sns+1,sns+1+cnt);
    #define cmp(a,b) ( dis[a.x][a.y] < dis[b.x][b.y] )
    queue<QueNode> qa,qb; QueNode tmp;
    for(int i=1;i<=cnt;i++) qa.push((QueNode){sns[i].x,sns[i].y});
    while( qa.size() || qb.size() ) {
        if( !qa.size() ) tmp = qb.front() , qb.pop();
        else if( !qb.size() || cmp(qa.front(),qb.front()) ) tmp = qa.front() , qa.pop();
        else tmp = qb.front() , qb.pop();
        for(int i=0;i<4;i++) {
            const int tx = tar[tmp.x][tmp.y][i].l , ty = tar[tmp.x][tmp.y][i].r;
            if( !~tx || !~ty ) continue;
            if( dis[tx][ty] > dis[tmp.x][tmp.y] + 1 ) dis[tx][ty] = dis[tmp.x][tmp.y] + 1 , qb.push((QueNode){tx,ty});
        }
    }
    #undef cmp
}


inline void dp() {
    for(int len=1;len<=k;len++) for(int st=0,ed=st+len-1;ed<k;st++,ed++) {
        for(int mid=st;mid<ed;mid++) for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
            f[st][ed][i][j] = min( f[st][ed][i][j] , f[st][mid][i][j] + f[mid+1][ed][i][j] );
        spfa(f[st][ed]);
    }
}

inline void getans() {
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ans = min( ans , f[0][k-1][i][j] );
}

int main() {
    scanf("%d%d%d",&k,&m,&n) , memset(f,0x3f,sizeof(f)) , ans = ****f;
    for(int i=1;i<=n;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=m;j++) if( isdigit(in[i][j]) ) f[in[i][j]-'1'][in[i][j]-'1'][i][j] = 0 , in[i][j] = '.';
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( in[i][j] != 'x' ) for(int dir=0;dir<4;dir++) tar[i][j][dir] = dfs(i,j,dir);
    dp() , getans();
    printf("%d\n",ans!=inf?ans:-1);
    return 0;
}

