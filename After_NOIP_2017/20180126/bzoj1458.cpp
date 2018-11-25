#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e2+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn*maxn<<3],nxt[maxn*maxn<<3],f[maxn*maxn<<3],dep[maxn];
int in[maxn][maxn],sum[maxn],tar[maxn];
int n,m,k,st,ed,ans;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
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

inline int cov(int x) {
    return x + n;
}
int main() {
    scanf("%d%d%d",&n,&m,&k);
    st = n + m + 1 , ed = st + 1;
    //debug<<"ed = "<<ed<<endl;
    for(int i=1;i<=n;i++)
        scanf("%d",tar+i);
    for(int i=1;i<=m;i++)
        scanf("%d",tar+cov(i));
    for(int i=1,a,b;i<=k;i++) {
        scanf("%d%d",&a,&b);
        in[a][b] = 1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            sum[i] += ( !in[i][j] ) ,
            sum[cov(j)] += ( !in[i][j] ) ,
            ans += ( !in[i][j] );
        }
    for(int i=1;i<=n+m;i++)
        if( sum[i] < tar[i] ) {
            puts("JIONG!");
            return 0;
        }
    for(int i=1;i<=n;i++)
        singledge(st,i,sum[i]-tar[i]);
    for(int j=1;j<=m;j++)
        singledge(cov(j),ed,sum[cov(j)]-tar[cov(j)]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( !in[i][j] )
                singledge(i,cov(j),1);
    printf("%d\n",ans-dinic());
    return 0;
}
