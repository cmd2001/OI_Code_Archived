#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=3e2+1e1,maxe=1e5+1e2;

int f[2][maxn][maxn],cur;
int s[maxn],t[maxe],nxt[maxe],l[maxe];
int n;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool trans() {
    cur ^= 1 , memset(f[cur],0x3f,sizeof(*f));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int at=s[j];at;at=nxt[at])
                f[cur][i][t[at]] = std::min( f[cur][i][t[at]] , f[cur^1][i][j] + l[at] );
    for(int i=1;i<=n;i++) {
        if( f[cur][i][i] < 0 ) return 1;
        f[cur][i][i] = 0;
    }
    return 0;
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l) ,
        addedge(a,b,l);
    }
    memset(f[cur],0x3f,sizeof(*f));
    for(int i=1;i<=n;i++) f[cur][i][i] = 0;
    for(int i=1;i<=n;i++)
        if( trans() ) return printf("%d\n",i),0;
    puts("0");
    return 0;
}
