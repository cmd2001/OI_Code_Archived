#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn=2e2+1e1,maxe=maxn*60;
const int inf=0x3f3f3f3f;

vector<int> tar[maxn][maxn];
int s[maxn<<1],t[maxe],nxt[maxe],f[maxe],cnt;
int dep[maxn<<1],st,ed;
int baks[maxn][maxn<<1],bakt[maxn][maxe],baknxt[maxn][maxe],bakf[maxn][maxe],bakcnt[maxn];
int expe[maxn],pir[maxn],way[maxn];
int n,m;

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
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
            ret += now , flow -= now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline int dinic() {
    return bfs()?dfs(st,inf):0;
}
inline void backup(int tim) {
    memcpy(baks[tim],s,sizeof(s)) ,
    memcpy(bakt[tim],t,sizeof(t)) ,
    memcpy(baknxt[tim],nxt,sizeof(nxt)) ,
    memcpy(bakf[tim],f,sizeof(f)) ,
    bakcnt[tim] = cnt ;
}
inline void restore(int tim) {
    memcpy(s,baks[tim],sizeof(s)) ,
    memcpy(t,bakt[tim],sizeof(t)) ,
    memcpy(nxt,baknxt[tim],sizeof(nxt)) ,
    memcpy(f,bakf[tim],sizeof(f)) ,
    cnt = bakcnt[tim];
}
inline int cov(int x) {
    return x + n;
}


inline bool judge(int x,int t) {
    restore(t) , singledge(st,x,1);
    for(int i=1;i<=expe[x];i++) for(unsigned j=0;j<tar[x][i].size();j++) {
        singledge(x,cov(tar[x][i][j]),1);
    }
    return dinic();
}
inline int bin(int x) {
    if( pir[x] <= expe[x] ) return 0;
    if( !judge(x,0) ) return x;
    int l = 0 , r = x - 1 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(x,mid) ) l = mid;
        else r = mid;
    }
    return x - l - 1;
}

inline void reset() {
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) tar[i][j].clear();
    memset(s,0,sizeof(s)) , cnt = 1;
}

int main() {
    static int T;
    scanf("%d%*d",&T);
    while(T--) {
        scanf("%d%d",&n,&m) , reset() , st = n + m + 1 , ed = n + m + 2;
        for(int i=1,w;i<=m;i++) scanf("%d",&w) , singledge(cov(i),ed,w);
        for(int i=1;i<=n;i++) for(int j=1,w;j<=m;j++) {
            scanf("%d",&w);
            if( w ) tar[i][w].push_back(j);
        }
        for(int i=1;i<=n;i++) scanf("%d",expe+i);
        for(int i=1;i<=n;i++) {
            backup(i-1);
            for(pir[i]=1;pir[i]<=m;pir[i]++) {
                restore(i-1) , singledge(st,i,1);
                for(unsigned j=0;j<tar[i][pir[i]].size();j++) {
                    singledge(i,cov(tar[i][pir[i]][j]),1);
                }
                if( dinic() ) break;
            }
        }
        for(int i=1;i<=n;i++) way[i] = bin(i);
        for(int i=1;i<=n;i++) printf("%d%c",pir[i],i!=n?' ':'\n');
        for(int i=1;i<=n;i++) printf("%d%c",way[i],i!=n?' ':'\n');
    }
    return 0;
}

