#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=1.5e2+1e1;
const int inf=0x3f3f3f3f;

namespace NetworkFlow {
    int s[maxn<<1],t[maxn*maxn<<3],nxt[maxn*maxn<<3],f[maxn*maxn<<3],c[maxn*maxn<<3];
    int dis[maxn<<1],sou[maxn<<1],inq[maxn<<1],st,ed;
    inline void coredge(int from,int to,int flow,int cost) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , c[cnt] = cost , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow,int cost) {
        coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
    }
    inline bool spfa() {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        std::queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
        }
        return dis[ed] != inf;
    }
    inline int release() {
        int ret = inf;
        for(int i=ed;i!=st;i=t[sou[i]^1]) ret = std::min( ret , f[sou[i]] );
        for(int i=ed;i!=st;i=t[sou[i]^1]) f[sou[i]] -= ret , f[sou[i]^1] += ret;
        return ret;
    }
    inline int flow() {
        int ret = 0;
        while( spfa() ) ret += dis[ed] * release();
        return ret;
    }
}

int dis[maxn][maxn];
int n,m,k;

inline void floyd() {
    for(int k=0;k<=n;k++) for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) if( k <= i || k <= j ) dis[i][j] = std::min( dis[i][j] , dis[i][k] + dis[k][j] );
}
inline void build() {
    using namespace NetworkFlow;
    #define cov(id,tpe) (id*2+tpe)
    st = n * 2 + 2 , ed = st + 1;
    for(int i=0;i<=n;i++) for(int j=i+1;j<=n;j++) if( ::dis[i][j] != inf ) singledge(cov(i,1),cov(j,0),inf,::dis[i][j]);
    for(int i=1;i<n;i++) singledge(st,cov(i,1),1,0) , singledge(cov(i,0),ed,1,0);
    singledge(st,cov(0,1),k,0) , singledge(cov(n,0),ed,1,0);
}

int main() {
    scanf("%d%d%d",&n,&m,&k) , memset(dis,0x3f,sizeof(dis));
    for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , dis[a][b] = dis[b][a] = std::min( dis[a][b] , l );
    floyd() , build() , printf("%d\n",NetworkFlow::flow());
    return 0;
}
