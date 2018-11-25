#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
const int maxn=5e3+1e2,maxe=125100,maxt=55,maxp=2.5e3+1e2;
const int inf=0x3f3f3f3f;

int u[maxp],v[maxp],lim[maxp];
int id[maxt][maxt];
int n,m,tar,su,cur,cnt,st,ed;

namespace Flow {
    int s[maxn],t[maxe<<3],nxt[maxe<<3],f[maxe<<3];
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
        std::queue<int> q; q.push(st);
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
                now = dfs(t[at],std::min(flow,f[at])) ,
                ret += now , flow -= now ,
                f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0 , now = 0;
        while( bfs() ) while( now = dfs(st,inf) ) ret += now;
        return ret;
    }
}

inline void add_level() {
    using namespace Flow;
    ++cur; for(int i=1;i<=n;i++) id[i][cur] = ++cnt;
    if( cur - 1 ) for(int i=1;i<=m;i++) singledge(id[u[i]][cur-1],id[v[i]][cur],lim[i]);
    singledge(st,id[1][cur],inf) , singledge(id[n][cur],ed,inf);
}

int main() {
    scanf("%d%d%d",&n,&m,&tar) , st = ++cnt , ed = ++cnt;
    for(int i=1;i<=m;i++) scanf("%d%d%d",u+i,v+i,lim+i);
    while( ( su += Flow::dinic() ) < tar ) add_level();
    printf("%d\n",cur-1);
    return 0;
}
