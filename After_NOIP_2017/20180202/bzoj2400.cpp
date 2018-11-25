#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxm=2e3+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],x[maxm],y[maxm];
int s[maxn],t[maxm<<4],nxt[maxm<<4],f[maxm<<4],cnt;
int dep[maxn];
int n,m,st,ed;
lli ans,cost;

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}
inline void doubledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,flow);
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
            now = dfs( t[at] , min( flow , f[at] ) );
            ret += now , flow -= now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() )
        while( now = dfs( st , inf ) )
            ret += now;
    return ret;
}
inline void build(int v) {
    memset(s,0,sizeof(s)) , cnt = 1;
    for(int i=1;i<=n;i++)
        if( in[i] >= 0 ) {
            if( ! ( ( in[i] >> v & 1 ) ) ) singledge(st,i,inf);
            else {
                singledge(i,ed,inf);
                singledge(st,i,1);
            }
        } else singledge(st,i,1);
    for(int i=1;i<=m;i++)
        doubledge( x[i] , y[i] , 10000 );
}
inline void calc(int v) {
    build(v);
    lli f = dinic();
    ans += ( 1ll << v ) * ( f / 10000 ) , cost += ( 1ll << v ) * ( f % 10000 );
}

int main() {
    scanf("%d%d",&n,&m) ;
    st = n + 1 , ed = n + 2;
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++) scanf("%d%d",x+i,y+i);
    for(int i=31;~i;i--)
        calc(i);
    printf("%lld\n%lld\n",ans,cost);
    return 0;
}


