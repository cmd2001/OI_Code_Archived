#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e4+1e3,maxl=1e2+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<4],nxt[maxn<<4],f[maxn<<4],pcnt;
int dep[maxn];
int in[maxl][maxl],id[maxl][maxl],tpe[maxl],srt[maxl],len;
int n,m,st,ed,ans;

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
    while( bfs() )
        while( now = dfs(st,inf) )
            ret += now;
    return ret;
}

inline int covfd(int x) {
    return x + pcnt;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",tpe+i) , srt[i] = tpe[i];
    sort(srt+1,srt+1+n);
    len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++)
        tpe[i] = lower_bound(srt+1,srt+1+len,tpe[i]) - srt;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n-i+1;j++) {
            scanf("%d",in[i]+j) , id[i][j] = ++pcnt;
            if( j == 1 ) in[i][j] -= srt[tpe[i]];
            if( in[i][j] >= 0 ) ans += in[i][j];
        }
    }
    st = pcnt + len + 1 , ed = pcnt + len + 2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n-i+1;j++) {
            if( in[i][j] >= 0 ) singledge(st,id[i][j],in[i][j]);
            else singledge(id[i][j],ed,-in[i][j]);
            if( j == 1 ) singledge(id[i][j],covfd(tpe[i]),inf);
            else {
                singledge(id[i][j],id[i][j-1],inf);
                if( i != n ) singledge(id[i][j],id[i+1][j-1],inf);
            }
        }
    for(int i=1;i<=len;i++)
        singledge(covfd(i),ed,m*srt[i]*srt[i]);
    
    printf("%d\n",ans-dinic());
    
    return 0;
}
