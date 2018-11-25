#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<queue>
const int maxn=65537,maxe=1e6+1e2,lim=32768;

int s[maxn],t[maxe<<1],nxt[maxe<<1],deg[maxn],cnt;
int u[maxe],v[maxe],lo[maxn],pows[maxn],id[maxn],dis[maxn],seq[maxn],sql;
int n,m;

inline void addedge(const int &from,const int &to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to];
}
inline void getseq() {
    memset(dis,-1,sizeof(dis)) , dis[1] = 0 , sql = 0;
    std::queue<int> q; q.push(1);
    while( q.size() ) {
        const int pos = q.front(); seq[++sql] = pos , q.pop();
        for(int at=s[pos];at;at=nxt[at]) if( !~dis[t[at]] ) dis[t[at]] = dis[pos] + 1 , q.push(t[at]);
    }
}
inline void solvepoint(int pos) {
    for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] == dis[pos] - 1 ) id[pos] |= id[t[at]];
}
inline void initid() {
    memset(id,0,sizeof(id));
    int cc = 0;
    for(int at=s[1];at;at=nxt[at]) id[t[at]] = pows[cc++];
}
inline bool diffbit(const int &x) {
    return x == ( x & -x );
}
inline bool judge() {
    static bool used[maxn];
    for(int i=1;i<=m;i++) if( !diffbit(id[u[i]]^id[v[i]]) ) return 0;
    memset(used,0,sizeof(used));
    for(int i=1;i<=n;i++) {
        if( id[i] >= n || used[id[i]] ) return 0;
        used[id[i]] = 1;
    }
    return 1;
}

inline void pre() {
    for(int i=2;i<=lim;i++) lo[i] = lo[i>>1] + 1;
    pows[0] = 1;
    for(int i=1;i<=16;i++) pows[i] = pows[i-1] << 1;
}

int main() {
    static int T,fail;
    scanf("%d",&T) , pre();
    while(T--) {
        scanf("%d%d",&n,&m) , memset(deg,0,sizeof(deg)) , memset(s,0,sizeof(s)) , fail = cnt = 0;
        for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , ++a , ++b , addedge(a,b) , addedge(b,a);
        if( pows[lo[n]] != n || m != ( n * lo[n] >> 1 ) ) fail = 1;
        for(int i=1;i<=n;i++) if( deg[i] != lo[n] ) fail = 1;
        if( fail ) { puts("-1"); continue; }
        initid() , getseq();
        for(int i=1;i<=n;i++) if( dis[seq[i]] > 1 ) solvepoint(seq[i]);
        if( !judge() ) puts("-1");
        else {
            for(int i=1;i<=n;i++) printf("%d ",id[i]);
            puts("");
        }
    }
    return 0;
}
