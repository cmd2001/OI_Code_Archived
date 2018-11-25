#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e4+1e2,maxe=1e2+1e1;
const int inf=0x3f3f3f3f;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

struct ANode {
    int x,y;
    friend bool operator < (const ANode &a,const ANode &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
}ans[maxn];

char in[maxe][maxe];
int col[maxe][maxe],id[maxe][maxe];
int px[maxn],py[maxn];
int s[maxn],t[maxn<<4],nxt[maxn<<4],f[maxn<<4],dep[maxn];
bool vis[maxn];
int n,m,sizl,sizr,st,ed,acnt,fl;

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
inline void findtar(int pos,int l,int r,int xx) {
    vis[pos] = 1;
    if( l <= pos && pos <= r ) ans[++acnt] = (ANode){px[pos],py[pos]};
    for(int at=s[pos];at;at=nxt[at]) if(f[at^xx]&&!vis[t[at]]) findtar(t[at],l,r,xx);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=m;j++) col[i][j] = ( ( i + j ) & 1 );
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( in[i][j] == '.' ) {
        if( !col[i][j] ) id[i][j] = ++sizl;
        else id[i][j] = ++sizr;
    }
    st = sizl + sizr + 1 , ed = st + 1;
    for(int i=1;i<=sizl;i++) singledge(st,i,1);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( in[i][j] == '.' && !col[i][j] ) {
        for(int k=0;k<4;k++) {
            const int tx = i + dx[k] , ty = j + dy[k];
            if( in[tx][ty] == '.' ) singledge(id[i][j],id[tx][ty]+sizl,1);
        }
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( in[i][j] == '.' ) {
        const int tid = ( !col[i][j] ) ? id[i][j] : id[i][j] + sizl;
        px[tid] = i , py[tid] = j;
    }
    for(int i=1;i<=sizr;i++) singledge(i+sizl,ed,1);
    fl = dinic();
    if( sizl + sizr == ( fl << 1 ) ) puts("LOSE");
    else {
        puts("WIN");
        findtar(st,1,sizl,0);
        memset(vis,0,sizeof(vis));
        findtar(ed,sizl+1,sizl+sizr,1);
        sort(ans+1,ans+acnt+1);
        for(int i=1;i<=acnt;i++)
            printf("%d %d\n",ans[i].x,ans[i].y);
    }
    return 0;
}

