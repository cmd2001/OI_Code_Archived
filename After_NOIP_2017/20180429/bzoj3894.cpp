#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=5e4+1e2,maxe=1e6+1e2,maxl=1e2+1e1;
const int inf=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

namespace Flow {
    int s[maxn],t[maxe],nxt[maxe],f[maxe],cnt=1;
    int dep[maxn],st,ed;
    inline void coredge(int from,int to,int flow) {
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
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && !~dep[t[at]] )
                    dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],min(flow,f[at])) ,
                ret += now , flow -= now , f[at] -= now , f[at^1] += now;
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

int sc[maxl][maxl],ar[maxl][maxl],ssc[maxl][maxl],sar[maxl][maxl];
int n,m,full,ans;

inline void build() {
    using namespace Flow;
    full = n * m + 1 , st = ++full , ed = ++full;
    #define cov(x,y) (m*(x-1)+y)
    #define legal(x,y) (0<x&&x<=n&&0<y&&y<=m)
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) singledge(st,cov(i,j),sc[i][j]) , singledge(cov(i,j),ed,ar[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
        int fsc = ++full , far = ++full;
        singledge(st,fsc,ssc[i][j]) , singledge(far,ed,sar[i][j]) , singledge(fsc,cov(i,j),inf) , singledge(cov(i,j),far,inf);
        for(int k=0;k<4;k++) {
            const int tx = i + dx[k] , ty = j + dy[k];
            if( legal(tx,ty) ) singledge(fsc,cov(tx,ty),inf) , singledge(cov(tx,ty),far,inf);
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",ar[i]+j) , ans += ar[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",sc[i]+j) , ans += sc[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",sar[i]+j) , ans += sar[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",ssc[i]+j) , ans += ssc[i][j];
    build() , ans -= Flow::dinic() , printf("%d\n",ans);
    return 0;
}
