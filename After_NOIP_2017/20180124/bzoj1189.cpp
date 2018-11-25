#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define bool unsigned char
using namespace std;
const int maxn=1.6e4+1e1,maxm=maxn*40,maxl=2e1+5e0;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<3],nxt[maxm<<3],f[maxm<<3],cnt;
int dep[maxn];
int dor[maxl][maxl],pos[maxl][maxl],cntd,cntp;
char in[maxl][maxl];
bool vis[maxl][maxl];
vector<int> dis[maxn],tar[maxn];
int n,m,st,ed;

namespace Inital {
    const int dx[]={0,0,1,-1} , dy[]={1,-1,0,0};
    inline void lable() {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if( in[i][j] == 'D' ) dor[i][j] = ++cntd;
                else if( in[i][j] == '.' ) pos[i][j] = ++cntp;
    }
    inline void bfs(int sx,int sy,int id) {
        static int len[maxl][maxl];
        memset(vis,0,sizeof(vis)); vis[sx][sy] = 1;
        memset(len,0,sizeof(len));
        queue<int> qx,qy; qx.push(sx) , qy.push(sy);
        while( qx.size() && qy.size() ) {
            const int x = qx.front() , y = qy.front(); qx.pop() , qy.pop();
            for(int i=0;i<4;i++) {
                const int tx = x + dx[i] , ty = y + dy[i];
                if( in[tx][ty] == '.' && !vis[tx][ty] ) {
                    vis[tx][ty] = 1 , len[tx][ty] = len[x][y] + 1 ,
                    qx.push(tx) , qy.push(ty);
                } else if( in[tx][ty] == 'D' ) {
                    tar[id].push_back(dor[tx][ty]) ,
                    dis[id].push_back(len[x][y]+1);
                }
            }
        }
    }
    inline void work() {
        lable();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if( pos[i][j] )
                    bfs(i,j,pos[i][j]);
    }
}

inline void coredge(int from,int to,int flow) {
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
                dep[t[at]] = dep[pos] + 1 ,
                q.push(t[at]);
            }
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
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
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

inline int covd(int pos,int t,int ft) {
    return cntp + ft * --pos + t;
}
inline void reset(int t) {
    memset(s,0,sizeof(s));
    cnt = 1;
    st = cntd * t + cntp + 1 , ed = st + 1;
}
inline void build(int t) {
    reset(t);
    for(int i=1;i<=cntp;i++) {
        singledge(st,i,1);
        for(unsigned j=0;j<tar[i].size();j++)
            if( dis[i][j] <= t ) {
                singledge(i,covd(tar[i][j],dis[i][j],t),1);
            }
    }
    for(int i=1;i<=cntd;i++)
        for(int tt=1;tt<=t;tt++) {
            singledge(covd(i,tt,t),ed,1);
            if( tt != t )
                singledge(covd(i,tt,t),covd(i,tt+1,t),inf);
        }
}
inline bool check(int x) {
    build(x);
    return dinic() == cntp;
}
inline int bin() {
    int l = 0 , r = 400 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( check(mid) ) r = mid;
        else l = mid;
    }
    return r;
}
inline bool judge() {
    for(int i=1;i<=cntp;i++)
        if( !tar[i].size() )
            return 1;
    return 0;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",in[i]+1);
    
    Inital::work();
    if( judge() ) return puts("impossible"),0;
    
    printf("%d\n",bin());
    
    return 0;
}
