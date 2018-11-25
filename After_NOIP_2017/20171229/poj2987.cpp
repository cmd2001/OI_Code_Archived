#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdlib>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e3+1e2,maxm=8e4+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

int s[maxn],t[maxm<<2],nxt[maxm<<2];
int dep[maxn];
lli f[maxm<<2];
lli ans,dd,per,away;
int n,m,st,ed;

inline void coredge(int from,int to,lli flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int from,int to,lli flow) {
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
                dep[t[at]] = dep[pos] + 1;
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
inline lli dinic() {
    lli ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

int main() {
    scanf("%d%d",&n,&m);
    st = n + 1 , ed = n + 2;
    for(int i=1;i<=n;i++) {
        lli vv;
        scanf("%lld",&vv);
        if( vv > 0 ) {
            ++away , ans += vv;
            vv = vv * ( n + 1 ) - 1; // different
            addedge(st,i,vv);
        }
        else {
            vv = -vv * ( n + 1 ) + 1;
            addedge(i,ed,vv);
        }
    }
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b,inf);
    }
    
    dd = dinic();
    ans = ans - ( dd + away ) / ( n + 1 ),
    per = ( dd + away ) % ( n + 1 );
    
    printf("%lld %lld\n",per,ans);
    
    return 0;
}