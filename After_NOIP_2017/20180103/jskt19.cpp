#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e2+1e2,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

lli dis[maxn][maxn];
int s[maxn<<1],t[maxm<<3],nxt[maxm<<3],f[maxm<<3],cnt;
int dep[maxn<<1];
int day[maxn<<1],nignt[maxn<<1];
int n,m,st,ed,full;

inline void floyd() {
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j] = min( dis[i][j] , dis[i][k] + dis[k][j] );
}

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow);
    coredge(to,from,0);
}

inline bool bfs() {
    memset(dep,-1,sizeof(dep));
    dep[st] = 0;
    queue<int> q;
    q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1,
                q.push(t[at]);
            }
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    if( pos == ed )
        return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at]));
            ret += now , flow -= now,
            f[at] -= now , f[at^1] += now;
            if( !flow )
                return ret;
        }
    if( !ret )
        dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

inline void init() {
    memset(s,0,sizeof(s));
    memset(t,0,sizeof(t));
    memset(f,0,sizeof(f));
    memset(nxt,0,sizeof(nxt));
    cnt = 1;
}
inline int cov(int id,int tp) { // 0 means from st , 1 means to ed
    return ( id << 1 ) - 1 + tp;
}
inline void build(lli lim) {
    init();
    for(int i=1;i<=n;i++)
        singledge(st,cov(i,0),day[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if( dis[i][j] <= lim ) {
                singledge(cov(i,0),cov(j,1),inf);
            }
    for(int i=1;i<=n;i++)
        singledge(cov(i,1),ed,nignt[i]);
}
inline bool judge(lli lim) {
    build(lim);
    return dinic() == full;
}

inline lli getans() {
    lli ll = -1 , rr = inf * 1000LL , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) )
            rr = mid;
        else
            ll = mid;
    }
    return rr!=inf*1000LL?rr:-1;
}

int main() {
    scanf("%d%d",&n,&m);
    st = n * 2 + 1 , ed = n * 2 + 2;
    for(int i=1;i<=n;i++)
        scanf("%d%d",day+i,nignt+i),
        full += day[i];
    memset(dis,inf,sizeof(dis));
    for(int i=1;i<=n;i++)
        dis[i][i] = 0;
    for(int i=1,a,b,d;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&d);
        dis[a][b] = dis[b][a] = min( dis[a][b] , (lli)d );
    }
    
    floyd();
    printf("%lld\n",getans());
    //cout<<judge(20)<<endl;
    
    return 0;
}
