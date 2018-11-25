#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=1e3+1e2,maxe=5e4+1e3,maxs=1<<4;
const int inf=0x3f3f3f3f,minf=0xefefefef;

int chain[5][maxn],onchain[maxn],id[maxn],c[maxn],dep[maxn]; // id of chain .
vector<int> pts[maxn]; // points of each level .
struct Edge {int u,v,b,d;}ine[maxe];
vector<Edge> es[maxn]; // edge of each level.
int f[55][1<<4][210],lns[210]; // f[level][statement][diffs]
int n,m,k,p,full,ans;

namespace Flow {
    int s[maxe],t[maxe<<2],nxt[maxe<<2],f[maxe<<2],cnt=1;
    int dep[maxe],st,ed;
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
    inline void reset(int fs) {
        memset(s+1,0,sizeof(int)*fs) , cnt = 1;
    }
}

inline int build(int dep,int sta,int mul) {
    using namespace Flow;
    st = pts[dep].size() + ( es[dep].size() * 2 ) + 1 , ed = st + 1 , reset(ed);
    #define cov(x,t) (x*2-1+t+pts[dep].size())'
    int ret = 0;
    for(unsigned i=0;i<es[dep].size();i++) {
        const int p = es[dep][i];
        if( on[p] ) { // & 1 means change it .
            if( ( sta >> ( id[p] - 1 ) ) & 1 ) singledge(p,ed,inf) , ret -= c[p];
            else singledge(st,p,inf);
        } else singledge(st,p,c[p]) , singledge(c[p],ed,inf);
    }
    for(unsigned i=0;i<es[dep].size();i++) {
        int o = cov(i,0) , h = cov(i,1);
        ret += es[i].b * mul , ret += es[i].d * mul;
        singledge(st,o,es[i].b*mul) , singledge(o,es[i].u,inf) , singledge(o,es[i].v,inf) ,
        siungledge(h,ed,es[i].d*mul) , singledge(es[i].u,h,inf) , singledge(es[i].v,h,inf);
    }
    return ret - dinic();
}
inline int calbet(int stfa,int stcur) {
    int dif = stfa ^ stcur , ret = 0;
    while( dif ) ++ret , dif -= ( dif & -dif );
    return ret;
}

inline void dp(int mul) {
    memset(f,0xef,sizeof(f));
    for(int i=0;i<full;i++) f[1][i][0] = build(1,i,mul);
    for(int i=0;i<n;i++) {
        for(int dif=0;dif<=n*m;i++)
            for(int cur=0;cur<full;cur++)
                if( f[i][cur][dif] != minf)
                    for(int nxt=0;nxt<full;nxt++) {
                        int nxtdif = dif + calbet(cur,nxt);
                        f[i+1][nxt][nxtdif] = max( f[i+1][nxt][nxddif] , f[i][cur][dif] + build(i+1,nxt) );
                    }
    }
    for(int i=0;i<full;i++) for(int dif=0;dif<=n*m;dif++) if( lns[dif] == mul ) ans = max( ans , f[n][i][dif] );
}

inline void pre() {
    for(int i=1;i<=n*k;i++) lns[i] = 10 * ln(i+1);
}

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        if( ( x = findfa(x) ) != ( y = findfa(y) ) ) fa[x] = y；
    }
    inline void init() {
        for(int i=1;i<=m;i++) fa[i] = i;
    }
}ufs;

int main() {
    static double dd;
    scanf("%d%d%d%d%*s",&n,&m,&k,&p) , ufs.init() , pre();
    for(int i=1;i<=m;i++) scanf("%d",c+i);
    for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) scanf("%d",chain[i]+j) , id[chain[i][j]] = i;
    for(int i=1;i<=p;i++) {
        scanf("%d%d%d%lf",&ine[i],&ine[i].v,&ine[i].d,&dd) , ine[i].b = floor( ine[i].d * dd ) , 
        ufs.merge(ine[i].u,ine[i].v);
    }
    for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) dep[ufs.findfa(chain[i][j])] = j;
    for(int i=1;i<=m;i++) {
        dep[i] = dep[ufs.findfa(i)];
        if( !dep[i] ) dep[i] = dep[ufs.findfa(i)] = 1;
        pts[dep[i]].push_back(i);
    }
    for(int i=1;i<=p;i++) es[dep[ine[i].u]].push_back(ine[i]);
    for(int i=lns[0];i<=lns[n*k];i++) dp(i);
    printf("%d\n",ans);
    return 0;
}
