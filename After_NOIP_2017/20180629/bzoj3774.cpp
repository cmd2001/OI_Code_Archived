#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e3+1e2,maxt=55;
const int inf=0x3f3f3f3f;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

int n,m,st,ed;
namespace NetworkFlow {
    int s[maxn],t[maxn<<5],nxt[maxn<<5],f[maxn<<5];
    int dep[maxn];
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
            }
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
}

int a[maxt][maxt],b[maxt][maxt],ans;

inline int cov(int i,int j,int tpe) {
    return ( m * --i + j ) * 2 - 1 + tpe;
}

int main() {
    scanf("%d%d",&n,&m) , st = 2 * n * m + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",a[i]+j);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",b[i]+j) , ans += b[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
        if( ( i + j ) & 1 ) NetworkFlow::singledge(st,cov(i,j,0),a[i][j]) , NetworkFlow::singledge(cov(i,j,0),cov(i,j,1),b[i][j]);
        else NetworkFlow::singledge(cov(i,j,0),ed,a[i][j]) , NetworkFlow::singledge(cov(i,j,1),cov(i,j,0),b[i][j]);
        for(int k=0;k<4;k++) {
            const int tx = i + dx[k] , ty = j + dy[k];
            if( 0 < tx && tx <= n && 0 < ty && ty <= m ) {
                if( ( i + j ) & 1 ) NetworkFlow::singledge(cov(i,j,1),cov(tx,ty,0),inf);
                else NetworkFlow::singledge(cov(tx,ty,0),cov(i,j,1),inf);
            }
        }
    }
    printf("%d\n",ans-NetworkFlow::dinic());
    return 0;
}

