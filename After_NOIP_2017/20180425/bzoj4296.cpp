#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define bool unsigned char
const int maxn=2e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],deg[maxn];
bool ban[maxn],vis[maxn];
int ans[maxn],seq[maxn],asl,sql,n,d;

inline void addedge(int from,int to) {
    static int cnt = 0;
    ++deg[t[++cnt]=to] , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    vis[seq[++sql]=pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( !ban[t[at]] && !vis[t[at]] ) dfs(t[at]);
}
inline void bfs() {
    std::queue<int> q;
    for(int i=1;i<=n;i++) if( deg[i] < d ) q.push(i) , ban[i] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at]) if( !ban[t[at]] ) if( --deg[t[at]] < d ) q.push(t[at]) , ban[t[at]] = 1;
    }
}
inline void getans() {
    for(int i=1;i<=n;i++) if( !ban[i] && !vis[i] ) {
        sql = 0 , dfs(i);
        if( sql > asl ) memcpy(ans+1,seq+1,sizeof(int)*(asl=sql));
    }
}

int main() {
    static int m;
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    bfs() , getans();
    if( !asl ) puts("NIE");
    else {
        printf("%d\n",asl) , std::sort(ans+1,ans+1+asl);
        for(int i=1;i<=asl;i++) printf("%d%c",ans[i],i!=asl?' ':'\n');
    }
    return 0;
}
