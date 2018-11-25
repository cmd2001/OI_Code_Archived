#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
using namespace std;
const int maxn=110,maxm=maxn*maxn;
const lli inf=0x3f3f3f3f3f3f3f3f;

int in[maxn][maxn];
int s[maxn],t[maxm<<2],nxt[maxm<<2];
lli f[maxm<<2];
int dep[maxn];
lli att[maxn],lif[maxn],sum;
int n,m,st,ed,cnt;

inline void coredge(int from,int to,lli flow) {
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,lli flow) {
    coredge(from,to,flow);
    coredge(to,from,0);
}

inline bool bfs() {
    memset(dep,-1,sizeof(dep)); dep[st] = 0;
    queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1 ,
                q.push(t[at]);
            }
    }
    return ~dep[ed];
}
inline lli dfs(int pos,lli flow) {
    if( pos == ed )
        return flow;
    lli ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(f[at],flow));
            ret += now , flow -= now ,
            f[at] -= now , f[at^1] += now;
            if( !flow )
                return ret;
        }
    if( !ret )
        dep[pos] = -1;
    return ret;
}
inline lli dinic() {
    lli ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

inline void reset() {
    memset(s,0,sizeof(s));
    cnt = 1;
}
inline int covr(int x) { // left m , right n.
    return x + m;
}
inline void build(lli t) {
    reset();
    for(int i=1;i<=m;i++)
        singledge(st,i,att[i]*t);
    for(int i=1;i<=n;i++)
        singledge(covr(i),ed,lif[i]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if( in[i][j] ) {
                singledge(i,covr(j),inf);
            }
}
inline bool judge(lli t) {
    build(t);
    return dinic() == sum;
}
inline lli getans() {
    lli l = -1 , r = inf / 10000 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid) )
            r = mid;
        else
            l = mid;
    }
    return r;
}

int main() {
    static double ans;
    scanf("%d%d",&n,&m);
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1;i<=n;i++) {
        scanf("%lld",lif+i);
        lif[i] *= 1000 , sum += lif[i];
    }
    for(int i=1;i<=m;i++)
        scanf("%lld",att+i);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",in[i]+j);

    ans = getans() / 1000.0;
    
    printf("%0.4lf\n",ans);
    
    return 0;
}