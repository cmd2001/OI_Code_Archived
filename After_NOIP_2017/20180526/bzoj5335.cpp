#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=5e2+1e1;
const int inf=0x3f3f3f3f;

int in[maxn][maxn],val[maxn];
int fa[maxn];
bool ban[maxn],vis[maxn];
int n,m,ans; // n is number of points .

namespace NetworkFlow {
    int s[maxn<<1],t[maxn*maxn<<2],nxt[maxn*maxn<<2],f[maxn*maxn<<2],cnt=1;
    int bs[maxn<<1],bf[maxn*maxn<<2],bcnt;
    int dep[maxn<<1],st,ed;
    inline void coredge(int from,int to,int flow) {
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        std::queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],std::min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
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
    inline void restore() {
        memcpy(s,bs,sizeof(s)) , memcpy(f+1,bf+1,sizeof(int)*bcnt),cnt = bcnt;
    }
    inline int cov(int id,int tpe) {
        return id * 2 - 1 + tpe;
    }
    inline void prebuild() {
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if( in[i][j] ) singledge(cov(i,0),cov(j,1),1);
        memcpy(bs,s,sizeof(s)) , memcpy(bf+1,f+1,sizeof(int)*cnt) , bcnt = cnt;
    }
    inline int calc(int lim) {
        int ret = 0;
        restore() , st = n * 2 + 1 , ed = st + 1;
        for(int i=1;i<=n;i++) if( val[i] < lim ) ++ret , singledge(st,cov(i,0),1) , singledge(cov(i,1),ed,1);
        return ret - dinic();
    }
}
inline int bin() {
    int l = -1 , r = inf + 1, mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( NetworkFlow::calc(mid) <= m + 1 ) l = mid;
        else r = mid;
    }
    return l;
}
inline void floyd() {
    for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) in[i][j] |= ( in[i][k] & in[k][j] );
}

int main() {
    scanf("%d%d",&m,&n);
    for(int i=1,k,x;i<=n;i++) {
        scanf("%d%d",val+i,&k);
        while(k--) scanf("%d",&x) , in[i][x] = 1;
    }
    floyd() , NetworkFlow::prebuild() , ans = bin();
    if( ans == inf ) puts("AK");
    else printf("%d\n",ans);
    return 0;
}
