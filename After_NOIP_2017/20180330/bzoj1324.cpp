#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e4+1e2,maxl=1e2+1e1;
const int inf=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

int in[maxl][maxl];
int s[maxn],t[maxn<<5],nxt[maxn<<5],f[maxn<<5],dep[maxn];
int n,m,st,ed,ans;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
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
            now = dfs(t[at],min(flow,f[at])) ,
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
inline void build() {
    #define cov(x,y) ((x-1)*m+y)
    #define legal(x,y) ( 1 <= x && x <= n && 1 <= y && y <= m )
    #define tpe(x,y) ((x+y)&1)
    st = n * m + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if( tpe(i,j) ) singledge(st,cov(i,j),in[i][j]);
            else singledge(cov(i,j),ed,in[i][j]);
            if( tpe(i,j) ) for(int k=0;k<4;k++) {
                const int tx = i + dx[k] , ty = j + dy[k];
                if( legal(tx,ty) ) singledge(cov(i,j),cov(tx,ty),inf);
            }
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",in[i]+j) , ans += in[i][j];
    build() , ans -= dinic();
    printf("%d\n",ans);
    return 0;
}