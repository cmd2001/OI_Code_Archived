#include<cstdio>
#include<cstring>
const int maxn=10;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

unsigned char vis[maxn][maxn];
int n,m,ans;

inline void dfs(int x,int y) {
    if( !x || !y || x == n || y == m ) return void(++ans);
    vis[x][y] = 1;
    for(int i=0;i<4;i++) {
        const int tx = x + dx[i] , ty = y + dy[i];
        if( !vis[tx][ty] ) dfs(tx,ty);
    }
    vis[x][y] = 0;
}

int main() {
    scanf("%d%d",&n,&m);
    if( n > m ) n ^= m ^= n ^= m;
    for(int i=1;i<n;i++) vis[i][0] = 1 , dfs(i,1) , vis[i][0] = 0;
    for(int i=1;i<m;i++) vis[0][i] = 1 , dfs(1,i) , vis[0][i] = 0;
    printf("%d\n",ans);
    return 0;
}
