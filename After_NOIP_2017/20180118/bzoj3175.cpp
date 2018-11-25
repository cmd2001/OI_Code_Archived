#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=4e4+1e2,maxl=2e2+1e1;
const int inf=0x3f3f3f3f;
const int dx[]={1,1,-1,-1,2,2,-2,-2},dy[]={2,-2,2,-2,1,-1,1,-1};

int in[maxl][maxl],col[maxl][maxl];
int s[maxn],t[maxn<<6],nxt[maxn<<6],f[maxn<<6];
int dep[maxn];
int st,ed;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow),
    coredge(to,from,0);
}
inline void doubledge(int from,int to,int flow) {
    coredge(from,to,flow),
    coredge(to,from,flow);
}

inline bool bfs() {
    memset(dep,-1,sizeof(dep)); dep[st] = 0;
    queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
            }
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at]));
            ret += now , flow -= now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() )
        while( now = dfs(st,inf) )
            ret += now;
    return ret;
}

int n,m,cnt;

inline int cov(int xx,int yy) {
    return m * --xx + yy;
}
inline bool judge(int x,int y) {
    return x > 0 && x <= n && y > 0 && y <= m && !in[x][y];
}
inline void initcol() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            col[i][j] = ! ( ( i + j ) & 1 );
}

int main() {
    static char s[maxl];
    scanf("%d",&n) , m = n;
    for(int i=1;i<=n;i++) {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
            in[i][j] = s[j] - '0';
    }
    
    st = n * m + 1 , ed = n * m + 2;
    initcol();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( !in[i][j] ) {
                ++cnt;
                if( col[i][j] ) singledge(st,cov(i,j),1);
                else singledge(cov(i,j),ed,1);
                if( col[i][j] )
                    for(int k=0;k<8;k++) {
                        const int tx = i + dx[k] , ty = j + dy[k];
                        if( judge(tx,ty) ) {
                            singledge(cov(i,j),cov(tx,ty),1);
                        }
                    }
            }
    
    printf("%d\n",cnt-dinic());
    
    return 0;
}

