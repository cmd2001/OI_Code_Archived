#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxe=maxn*maxn;
const lli inf=0x3f3f3f3f3f3f3f3f;

int a[maxn],b[maxn];
int s[maxn],t[maxe],nxt[maxe],dep[maxn];
lli f[maxe],ans;
int st,ed;

inline void coredge(int from,int to,lli flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,lli flow) {
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
inline lli dfs(int pos,lli flow) {
    if( pos == ed ) return flow;
    lli ret = 0 , now = 0;
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
    while( bfs() )
        while( now = dfs(st,inf) )
            ret += now;
    return ret;
}

inline lli gcd(register lli x,register lli y) {
    register lli t;
    while( t = x % y )
        x = y , y = t;
    return y;
}
inline bool judge(lli x,lli y) {
    lli t = x * x + y * y;
    lli sq = sqrt(t);
    if( sq * sq != t ) return 1;
    return gcd(x,y) != 1;
}
int main() {
    static int n;
    scanf("%d",&n) , st = n + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i) , ans += b[i];
    for(int i=1;i<=n;i++)
        if( a[i] & 1 ) singledge(st,i,b[i]);
        else singledge(i,ed,b[i]);
    for(int i=1;i<=n;i++)
        if( a[i] & 1 )
            for(int j=1;j<=n;j++)
                if( ! ( a[j] & 1 ) )
                    if( !judge(a[i],a[j]) )
                        singledge(i,j,inf);
    ans -= dinic();
    printf("%lld\n",ans);
    return 0;
}

