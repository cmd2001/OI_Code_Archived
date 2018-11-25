#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
typedef long long int lli;
const int maxn=5e3+1e2,maxe=1e5+1e2;
const lli inf = 0x3f3f3f3f3f3f3f3fll;

struct Graph {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],l[maxe<<1],cnt;
    lli dis[maxn]; bool inq[maxn];
    const lli& operator [] (const int &x) const { return dis[x]; }
    inline void coredge(int from,int to,int len) {
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void spfa(int st) {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        std::queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
        }
    }
}gra,rev;

int u[maxe],v[maxe],l[maxe];
lli ans = inf;

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",u+i,v+i,l+i) , gra.addedge(u[i],v[i],l[i]) , rev.addedge(u[i],v[i],l[i]);
    gra.spfa(1) , rev.spfa(n);
    for(int i=1;i<=m;i++) {
        if( gra[u[i]] + rev[v[i]] + l[i] > gra[n] ) ans = std::min( ans , gra[u[i]] + rev[v[i]] + l[i] );
        if( gra[v[i]] + rev[u[i]] + l[i] > gra[n] ) ans = std::min( ans , gra[v[i]] + rev[u[i]] + l[i] );
    }
    printf("%lld\n",ans);
    return 0;
}
