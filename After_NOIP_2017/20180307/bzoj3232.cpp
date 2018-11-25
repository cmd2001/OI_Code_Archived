#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2.5e3+1e2,maxl=5e1+5;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int in[maxl][maxl],x[maxl][maxl],y[maxl][maxl];
int s[maxn],t[maxn<<5],nxt[maxn<<5],cnt;
lli f[maxn<<5];
int dep[maxn];
int n,m,st,ed;

inline void coredge(int from,int to,lli flow) {
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
            now = dfs(t[at],min(flow,f[at])) ,
            ret += now , flow -= now ,
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

inline void reset() {
    memset(s,0,sizeof(s)) , cnt = 1;
}
inline int cov(int x,int y) {
    return ( x - 1 ) * m + y;
}
inline void rebuild(lli mid) {
    reset() , st = n * m + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) singledge(st,cov(i,j),in[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
        if( i == 1 ) singledge(cov(i,j),ed,x[i][j]*mid);
        else singledge(cov(i,j),cov(i-1,j),x[i][j]*mid);
        if( i == n ) singledge(cov(i,j),ed,x[i+1][j]*mid);
        else singledge(cov(i,j),cov(i+1,j),x[i+1][j]*mid);
        if( j == 1 ) singledge(cov(i,j),ed,y[i][j]*mid);
        else singledge(cov(i,j),cov(i,j-1),y[i][j]*mid);
        if( j == m ) singledge(cov(i,j),ed,y[i][j+1]*mid);
        else singledge(cov(i,j),cov(i,j+1),y[i][j+1]*mid);
    }
}
inline lli judge(lli mid) {
    lli ret = 0;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ret += in[i][j];
    rebuild(mid) , ret -= dinic();
    return ret;
}
inline lli bin() {
    lli ll = 0 , rr = inf / 100000 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) > 0 ) ll = mid;
        else rr = mid;
    }
    if( judge(rr) >= 0 ) return rr;
    return ll;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",in[i]+j) , in[i][j] *= 100000;
    for(int i=1;i<=n+1;i++) for(int j=1;j<=m;j++) scanf("%d",x[i]+j);
    for(int i=1;i<=n;i++) for(int j=1;j<=m+1;j++) scanf("%d",y[i]+j);
    double ans = (double) bin() / 100000;
    printf("%0.3lf\n",ans);
    return 0;
}
