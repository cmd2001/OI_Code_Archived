#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

int n,m,e;

namespace Flow {
    int s[maxn],t[maxe],nxt[maxe],f[maxe];
    int dep[maxn],st,ed;
    
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
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],std::min(flow,f[at])) ,
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
    inline int findtar(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( !f[at] && t[at] != st ) return t[at] - n;
        return 0;
    }
}
using namespace Flow;

int main() {
    scanf("%d%d%d",&n,&m,&e) , st = n + m + 1 , ed = st + 1;
    #define cov(x) (x+n)
    for(int i=1;i<=n;i++) singledge(st,i,1);
    for(int i=1;i<=m;i++) singledge(cov(i),ed,1);
    for(int i=1,a,b;i<=e;i++) scanf("%d%d",&a,&b) , singledge(a,cov(b),1);
    printf("%d\n",dinic());
    for(int i=1;i<=n;i++) printf("%d%c",findtar(i),i!=n?' ':'\n');
    return 0;
}
