#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
const int maxn=3e3+1e2,maxe=3e6+1e2;
const int inf=0x3f3f3f3f;

int in[maxn];
int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1];
int dep[maxn];
int n,st,ed,ans;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
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
            now = dfs(t[at],std::min(flow,f[at]));
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

inline int gcd(int x,int y) {
    while( ! ( x && y ) ) return x | y;
    register int t;
    while( t = x % y )
        x = y , y = t;
    return y;
}
inline bool judge(int x,int y) {
    int c = sqrt( x * x + y * y );
    if( c * c != x * x + y * y ) return 0;
    return gcd(x,y) == 1;
}

int main() {
    scanf("%d",&n) , st = n + 1 , ed = n + 2;
    for(int i=1;i<=n;i++) scanf("%d",in+i) , ans += in[i];
    for(int i=1;i<=n;i++)
        if( in[i] & 1 )
            for(int j=1;j<=n;j++)
                if( ! ( in[j] & 1 ) ) {
                    if( judge(in[i],in[j]) )
                        singledge(i,j,inf);
                }
    for(int i=1;i<=n;i++)
        if( in[i] & 1 ) singledge(st,i,in[i]);
        else singledge(i,ed,in[i]);
    ans -= dinic();
    printf("%d\n",ans);
    return 0;
}
