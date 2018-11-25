#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
const int maxn=1.6e3+1e2,maxe=maxn<<5,maxt=4e1+5e0;
const lli inf=0x3f3f3f3f3f3f3f3fll;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

lli in[maxt][maxt];
int col[maxt][maxt],id[maxt][maxt];
int s[maxn],t[maxe],nxt[maxe],dep[maxn],cnt;
lli f[maxe],sizw,sizb,sumw,sumb;
int n,m,st,ed;

inline void coredge(int from,int to,lli flow) {
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,lli flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}
inline bool bfs() {
    memset(dep,-1,sizeof(dep)) , dep[st] = 0;
    std::queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] )
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
    }
    return ~dep[ed];
}
inline lli dfs(int pos,lli flow) {
    if( pos == ed ) return flow;
    lli ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],std::min(flow,f[at]));
            ret += now , flow -= now,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline lli dinic() {
    lli ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) ) ret += now;
    }
    return ret;
}
inline void rebuild(lli x) {
    st = id[n][m] + 1 , ed = st + 1;
    memset(s,0,sizeof(s)) , cnt = 1;
    #define legal(a,b) (0<a&&a<=n&&0<b&&b<=m)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( col[i][j] ) singledge(id[i][j],ed,x-in[i][j]);
            else {
                singledge(st,id[i][j],x-in[i][j]);
                for(int t=0;t<4;t++) {
                    const int tx = i + dx[t] , ty = j + dy[t];
                    if( legal(tx,ty) ) singledge(id[i][j],id[tx][ty],inf);
                }
            }
}
inline bool judge(lli x) {
    rebuild(x);
    return dinic() + sumw == x * sizw;
}
inline lli bin() {
    lli l = 0 , r = inf , mid;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) l = std::max( l , in[i][j] );
    --l;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid) ) r = mid;
        else l = mid;
    }
    return r;
}
inline bool can(lli x) {
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( x < in[i][j] ) return 0;
    return judge(x);
}
inline lli cov(lli x) {
    return x * sizw - sumw;
}

inline void init() {
    sizb = sizw = sumb = sumw = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            col[i][j] = ( i + j ) & 1 ,
            id[i][j] = ( i - 1 ) * m + j ;
            if( col[i][j] ) ++sizw , sumw += in[i][j];
            else ++sizb , sumb += in[i][j];
        }
}

int main() {
    static int T;
    scanf("%d",&T);
    while( T-- ) {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%lld",in[i]+j);
        init();
        if( sizb != sizw ) {
            const lli ans = ( sumb - sumw ) / ( sizb - sizw );
            if( can(ans) ) printf("%lld\n",cov(ans));
            else puts("-1");
        } else {
            if( sumb != sumw ) puts("-1");
            else printf("%lld\n",cov(bin()));
        }
    }
    return 0;
}


