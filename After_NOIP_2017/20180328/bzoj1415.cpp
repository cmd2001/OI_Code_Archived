#include<cstdio>
#include<cstring>
#include<queue>
const int maxn=1e3+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],deg[maxn],dis[maxn];
int way[maxn][maxn];
double f[maxn][maxn];

inline void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to];
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline double dp(int pos,int tar) {
    if( f[pos][tar] ) return f[pos][tar]; // statement visited .
    if( pos == tar ) return 0; // at the same point .
    if( way[pos][tar] == tar || way[way[pos][tar]][tar] == tar ) return f[pos][tar] = 1;
    double sum = dp(way[way[pos][tar]][tar],tar);
    for(int at=s[tar];at;at=nxt[at]) sum += dp(way[way[pos][tar]][tar],t[at]);
    return f[pos][tar] = sum / ( deg[tar] + 1 ) + 1;
}

inline void bfs(int st) {
    memset(dis,-1,sizeof(dis)) , dis[st] = 0;
    std::queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        const int tp = way[st][pos];
        for(int at=s[pos];at;at=nxt[at])
            if( !~dis[t[at]] || ( dis[t[at]] == dis[pos] + 1 && tp < way[st][t[at]] ) ) {
                dis[t[at]] = dis[pos] + 1 , q.push(t[at]);
                way[st][t[at]] = tp ? tp : t[at];
            }
    }
}

int main() {
    static int n,m,pos,tar;
    scanf("%d%d%d%d",&n,&m,&pos,&tar);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b) , addedge(a,b);
    }
    for(int i=1;i<=n;i++) bfs(i);
    printf("%0.3lf\n",dp(pos,tar));
    return 0;
}
