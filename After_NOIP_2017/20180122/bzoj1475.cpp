#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e4+1e2,maxl=1e2+1e1;
const int inf=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

int s[maxn],t[maxn<<5],nxt[maxn<<5],f[maxn<<5];
int in[maxl][maxl],col[maxl][maxl];
int dep[maxn];
int n,m,st,ed,ans;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
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
            now = dfs( t[at] , min(flow,f[at]) );
            ret += now , flow -= now,
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

inline bool judge(int xx,int yy) {
    return xx > 0 && xx <= n && yy > 0 && yy <= m;
}
inline int cov(int xx,int yy) {
    return m * --xx + yy;
}

int main() {
    scanf("%d",&n) , m = n;
    st = n * m + 1 , ed = st + 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",in[i]+j) ,
            ans += in[i][j] ,
            col[i][j] = ! ( ( i + j ) & 1 );
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( col[i][j] ) {
                singledge(st,cov(i,j),in[i][j]);
                for(int k=0;k<4;k++) {
                    const int tx = i + dx[k] , ty = j + dy[k];
                    if( judge(tx,ty) )
                        singledge(cov(i,j),cov(tx,ty),inf);
                }
            } else singledge(cov(i,j),ed,in[i][j]);
    
    printf("%d\n",ans-dinic());
    return 0;
}
