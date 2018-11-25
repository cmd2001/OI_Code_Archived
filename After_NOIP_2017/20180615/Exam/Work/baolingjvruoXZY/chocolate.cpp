#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=25,maxs=1<<9;
const int inf=0x3f3f3f3f;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

int bin[maxs];
struct Node {int x,y,s;};
int a[maxn][maxn],b[maxn][maxn];
int f[2][maxn][maxn][maxs];
bool inq[2][maxn][maxn][maxs];
queue<Node> q[2];
int n,m,k,cur,ans;

inline void update(int &dst,const int &x) {
    dst = min( dst , x );
}
inline void trans() { // it works well under random input data .
    #define legal(x,y) (0<=x&&x<n&&0<=y&&y<m)
    while( q[cur^1].size() ) {
        const int x = q[cur^1].front().x , y = q[cur^1].front().y , s = q[cur^1].front().s; q[cur^1].pop();
        for(int i=0;i<4;i++) {
            const int tx = x + dx[i] , ty = y + dy[i];
            if( legal(tx,ty) && ~a[tx][ty]) {
                const int ts = s | ( 1 << a[tx][ty] ) , tf = f[cur^1][x][y][s] + b[tx][ty];
                if( bin[ts] >= k ) update(ans,tf);
                if( tf < ans ) {
                    update(f[cur][tx][ty][ts],tf);
                    if( !inq[cur][tx][ty][ts] ) q[cur].push((Node){tx,ty,ts}) , inq[cur][tx][ty][ts] = 1;
                }
            }
        }
        f[cur^1][x][y][s] = inf , inq[cur^1][x][y][s] = 0;
    }
    #undef legal
}

int main() {
    static int T;
    freopen("chocolate.in","r",stdin);
    freopen("chocolate.out","w",stdout);
    scanf("%d",&T) , memset(f,0x3f,sizeof(f));
    for(int i=1;i<maxs;i++) bin[i] = bin[i>>1] + ( i & 1 );
    while(T--) {
        scanf("%d%d%d",&n,&m,&k) , cur = 0 , ans = inf;
        if( !k ) { puts("0"); continue; }
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) scanf("%d",a[i]+j);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) scanf("%d",b[i]+j);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) if( ~a[i][j] ) {
            f[cur][i][j][1<<a[i][j]] = b[i][j];
            if( !inq[cur][i][j][1<<a[i][j]] ) q[cur].push((Node){i,j,1<<a[i][j]});
        }
        for(int i=2;i<=n*m;i++) cur ^= 1 , trans();
        printf("%d\n",ans==inf?-1:ans);
    }
    fclose(stdout);
    return 0;
}

