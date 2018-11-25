#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxe=1e4+1e2;
const int inf=0x3f3f3f3f;

double in[maxn][maxn],flr[maxn][maxn];
int s[maxn<<1],t[maxe<<4],nxt[maxe<<4],f[maxe<<4],cnt=1;
int b[maxe<<4],bcnt;
int dep[maxn<<1],deg[maxn<<1];
int st,ed,_s,_t;

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow , 
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
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
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0;
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
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

int main() {
    static int n,f,lim;
    scanf("%d",&n) , _s = (n<<1) + 1 , _t = _s + 1 , st = _t + 1 , ed = st + 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%lf",in[i]+j) , flr[i][j] = floor(in[i][j]);
    for(int i=1;i<n;i++) {
        deg[_s] += flr[i][n] , deg[i] -= flr[i][n] ,
        deg[_t] -= flr[n][i] , deg[i+n] += flr[n][i];
        if( in[i][n] != flr[i][n] ) singledge(_s,i,1);
        if( in[n][i] != flr[n][i] ) singledge(i+n,_t,1);
    }
    for(int i=1;i<n;i++)
        for(int j=1;j<n;j++) {
            deg[i] += flr[i][j] , deg[j+n] -= flr[i][j];
            if( in[i][j] != flr[i][j] ) singledge(i,j+n,1);
        }
    singledge(_t,_s,inf);
    for(int i=1;i<n;i++) {
        if( deg[i] > 0 ) singledge(i,ed,deg[i]) , lim += deg[i];
        else singledge(st,i,-deg[i]);
        if( deg[i+n] > 0 ) singledge(i+n,ed,deg[i+n]) , lim += deg[i+n];
        else singledge(st,i+n,-deg[i+n]);
    }
    singledge(_s,ed,deg[_s]) , singledge(st,_t,-deg[_t]);
    
    if( dinic() < lim ) puts("No");
    else {
        st = _s , ed = _t;
        f = dinic();
        printf("%d\n",f*3);
    }
    return 0;
}
