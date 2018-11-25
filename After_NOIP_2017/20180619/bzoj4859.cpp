#include<cstdio>
#include<cstring>
const int maxn=3e1+1e1,maxw=1e1+1e1;
const int mod=1e9+9;

int dx[maxw],dy[maxw],dxx[maxw],dyy[maxw],dl,dll;
int f[maxn][maxn][maxn][maxn],g[3][3][3][3];
char in[maxn][maxn];
int n,m;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void sube(int &dst,const int &x) {
    if( ( dst -= x ) < 0 ) dst += mod;
}
#define legal(x,y) (0<x&&x<=n&&0<y&&y<=m)
inline int dfs(int x,int y,int xx,int yy) {
    if( ~f[x][y][xx][yy] ) return f[x][y][xx][yy];
    f[x][y][xx][yy] = 0;
    for(int i=1;i<=dl;i++) for(int j=1;j<=dll;j++) {
        const int tx = x + dx[i] , ty = y + dy[i] , txx = xx + dxx[j] , tyy = yy + dyy[j];
        if( legal(tx,ty) && legal(txx,tyy) && in[tx][ty] == in[txx][tyy] ) adde(f[x][y][xx][yy],add(dfs(tx,ty,txx,tyy),1));
    }
    return f[x][y][xx][yy];
}
inline int core_solve(int tx,int ty,int txx,int tyy) {
    if( ~g[tx+1][ty+1][txx+1][tyy+1] ) return g[tx+1][ty+1][txx+1][tyy+1];
    int ret = 0;
    memset(f,-1,sizeof(f)) , dl = dll = 0;
    for(int i=-1;i<=1;i++) if( !i || i == tx ) for(int j=-1;j<=1;j++) if( !j || j == ty ) if( i || j ) dx[++dl] = i , dy[dl] = j;
    for(int i=-1;i<=1;i++) if( !i || i == txx ) for(int j=-1;j<=1;j++) if( !j || j == tyy ) if( i || j ) dxx[++dll] = i , dyy[dll] = j;
    for(int x=1;x<=n;x++) for(int y=1;y<=m;y++) for(int xx=1;xx<=n;xx++) for(int yy=1;yy<=m;yy++) if( in[x][y] == in[xx][yy] ) adde(ret,dfs(x,y,xx,yy));
    return g[tx+1][ty+1][txx+1][tyy+1] = g[txx+1][tyy+1][tx+1][ty+1] = g[1-tx][1-ty][1-txx][1-tyy] = g[1-txx][1-tyy][1-tx][1-ty] = ret;
}
inline int solve(int tx,int ty) {
    int ret = 0;
    for(int i=-1;i<=1;i++) for(int j=-1;j<=1;j++) if( i || j ) {
        if( i && j ) adde(ret,core_solve(tx,ty,i,j));
        else sube(ret,core_solve(tx,ty,i,j));
    }
    return ret;
}
inline int getans() {
    int ret = 0;
    for(int i=-1;i<=1;i++) for(int j=-1;j<=1;j++) if( i || j ) {
        if( i && j ) adde(ret,solve(i,j));
        else sube(ret,solve(i,j));
    }
    return ret;
}

int main() {
    scanf("%d%d",&n,&m) , memset(g,-1,sizeof(g));
    for(int i=1;i<=n;i++) scanf("%s",in[i]+1);
    printf("%d\n",getans());
    return 0;
}
