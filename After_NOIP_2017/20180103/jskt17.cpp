#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxm=maxn*maxn<<1;
const int inf=0x3f3f3f3f;

int n,m,from,to,mid;

namespace NetworkFlow {
    int s[maxn],t[maxm<<2],nxt[maxm<<2],f[maxm<<2],cnt;
    int dep[maxn],st,ed;
    
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
        cnt = 1;
        memset(s,0,sizeof(s));
    }
}
namespace Path {
    int s[maxn],t[maxm],nxt[maxm],vis[maxn],cnt;
    
    inline void addedge(int from,int to) {
        //debug<<"from = "<<from<<"to = "<<to<<endl;
        t[++cnt] = to,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos) {
        printf("%d",pos);
        putchar(pos!=to?' ':'\n');
        vis[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( vis[t[at]] ) {
                dfs(t[at]);
                return;
            }
    }
    
    inline void init() {
        cnt = 0;
        memset(s,0,sizeof(s));
    }
}

inline void trans() {
    using namespace NetworkFlow;
    for(int i=1;i<st;i+=2)
        for(int at=s[i];at;at=nxt[at])
            if( !f[at] && t[at] == i + 1 )
                Path::vis[(i+1)>>1] = 1;
    Path::vis[mid] = 1;
    for(int i=2;i<st;i+=2)
        for(int at=s[i];at;at=nxt[at])
            if( (!(at&1)) && !f[at] && t[at]!=ed ) {
                using Path::addedge;
                //debug<<"i= "<<(i>>1)<<"t[at] = "<<((t[at]+1)>>1)<<endl;
                addedge(i>>1,(t[at]+1)>>1);
                addedge((t[at]+1)>>1,i>>1);
            }
}

inline void init() {
    NetworkFlow::init();
    Path::init();
}
inline int cov(int id,int sta) { // 0 means in point , 1 means out point
    return ( id << 1 ) - 1 + sta;
}


int main() {
    static int T;
    scanf("%d",&T);
    while( T-- ) {
        init();
        scanf("%d%d",&n,&m);
        scanf("%d%d%d",&from,&to,&mid);
        using NetworkFlow::st;
        using NetworkFlow::ed;
        st = n * 2 + 1 , ed = n * 2 + 2;
        for(int i=1;i<=n;i++)
            NetworkFlow::singledge(cov(i,0),cov(i,1),1);
        for(int i=1,a,b;i<=m;i++) {
            using NetworkFlow::singledge;
            scanf("%d%d",&a,&b);
            singledge(cov(a,1),cov(b,0),1);
            singledge(cov(b,1),cov(a,0),1);
        }
        NetworkFlow::singledge(st,cov(mid,1),2);
        NetworkFlow::singledge(cov(from,1),ed,1);
        NetworkFlow::singledge(cov(to,1),ed,1);
        
        NetworkFlow::dinic();
        trans();
        
        Path::dfs(from);
        
    }
    
    return 0;
}
