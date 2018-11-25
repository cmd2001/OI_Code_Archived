#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
using namespace std;
const int maxn=1e3+1e1,maxm=maxn*maxn;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int s[maxn],t[maxm<<2],nxt[maxm<<2];
lli f[maxm<<2],ans;
int dep[maxn];
int n,m,st,ed;

inline void coredge(int from,int to,lli flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,lli flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}
inline void doubledge(int from,int to,lli flow) {
    coredge(from,to,flow) , coredge(to,from,flow);
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
    if( pos == ed ) return flow;
    lli ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at]));
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
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

int main() {
    static lli x,su;
    scanf("%d",&n);
    st = n + 1 , ed = n + 2;
    for(int i=1;i<=n;i++) {
        scanf("%lld",&x);
        singledge(i,ed,x);
    }
    for(int i=1;i<=n;i++) {
        su = 0;
        for(int j=1;j<=n;j++) {
            scanf("%lld",&x);
            su += x , ans += x;
            if( j > i ) doubledge(i,j,x<<1);
        }
        singledge(st,i,su);
    }
    
    printf("%lld\n",ans-dinic());
    
    return 0;
}