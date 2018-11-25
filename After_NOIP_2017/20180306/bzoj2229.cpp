#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
using std::min;
const int maxn=1.5e2+1e1,maxe=3e3+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int s[maxn],t[maxe<<3],nxt[maxe<<3],dep[maxn],cnt;
lli f[maxe<<3],b[maxe<<3],c[maxn][maxn];
int id[maxn],gcn;
int n,m,ans,st,ed;

inline void coredge(int from,int to,lli flow) {
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to,lli flow) {
    coredge(from,to,flow) , coredge(to,from,flow);
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
inline lli dinic() {
    lli ret = 0 , now = 0;
    while( bfs() ) {
        while( ( now = dfs(st,inf) ) )
            ret += now;
    }
    return ret;
}

inline void solve(int bid,int siz) {
    if( siz == 1 ) return;
    st = ed = 0;
    memcpy(f,b,sizeof(b));
    for(int i=1;i<=n;i++) if( id[i] == bid ) {
        if( !st ) st = i;
        else if( !ed ) ed = i;
    }
    lli cost = dinic();
    int sizl=0,sizr=0,gl=++gcn,gr=++gcn;
    for(int i=1;i<=n;i++)
        if( id[i] == bid ) {
            if( ~dep[i] ) id[i] = gl , ++sizl;
            else id[i] = gr , ++sizr;
        }
    for(int i=1;i<=n;i++)
        if( ~dep[i] )
            for(int j=1;j<=n;j++)
                if( !~dep[j] )
                    c[i][j] = c[j][i] = min( c[i][j] , cost ) ;
    solve(gl,sizl) , solve(gr,sizr);
}
inline void reset() {
    memset(s,0,sizeof(s)) , cnt = 1 , gcn = 1;
    for(int i=1;i<=n;i++) id[i] = gcn;
    memset(c,0x3f,sizeof(c));
}

int main() {
    static int T,t,lim;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m) , reset();
        for(int i=1,aa,bb,ff;i<=m;i++) {
            scanf("%d%d%d",&aa,&bb,&ff) ,
            doubledge(aa,bb,ff);
        }
        scanf("%d",&t) , memcpy(b,f,sizeof(f));
        solve(1,n);
        while(t--) {
            scanf("%d",&lim) , ans = 0;
            for(int i=1;i<=n;i++)
                for(int j=1;j<i;j++)
                    if( c[i][j] <= lim )
                        ++ans;
            printf("%d\n",ans);
        }
        putchar('\n');
    }
    return 0;
}

