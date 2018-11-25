#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=7e2+1e1;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

int in[maxn][maxn],f[maxn][maxn];
bool can[maxn][maxn];

inline int dfs(int x,int y) {
    if( ~f[x][y] ) return f[x][y];
    f[x][y] = 1;
    for(int i=0;i<4;i++) {
        const int tx = x + dx[i] , ty = y + dy[i];
        if( can[tx][ty] && in[x][y] > in[tx][ty] ) f[x][y] = std::max( f[x][y] ,dfs(tx,ty) + 1 );
    }
    return f[x][y];
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch , fix = 1;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}
inline void getstr(char* s) {
    char ch;
    while( !isalpha(ch=nextchar()) );
    do *s++ = ch; while( isalpha(ch=nextchar()) );
}

int main() {
    static int n;
    static char o[10];
    n = getint();
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) in[i][j] = getint() , can[i][j] = 1;
    for(int i=1,m=getint(),a,b,c,d;i<=m;i++) {
        getstr(o);
        if( *o == 'Q' ) {
            int ans = 0;
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j] = -1;
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if( can[i][j] ) ans = std::max( ans , dfs(i,j) );
            printf("%d\n",ans);
        } else if( *o == 'C' ) a = getint() , b = getint() , in[a][b] = getint();
        else {
            a = getint() , b = getint() , c = getint() , d = getint();
            for(int i=a;i<=c;i++) for(int j=b;j<=d;j++) can[i][j] = *o == 'B';
        }
    }
    return 0;
}
