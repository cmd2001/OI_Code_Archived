#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=2e2+1e1,maxe=1e4+1e2;
const int inf=0x3f3f3f3f;

namespace Flow {
    int s[maxn],t[maxe<<5],nxt[maxe<<5],f[maxe<<5],c[maxe<<5];
    int dis[maxn],sou[maxn],inq[maxn],st,ed;
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
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
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
    inline void flow(int &cst,int &su) {
        int now = 0;
        while( spfa() ) now = release() , cst += now * dis[ed] , su += now;
    }
}

int n,m;

inline int gid(int x,int y) {
    return m * --x + y;
}
inline int cov(int x,int y,int tpe) {
    return gid(x,y) * 2 - 1 + tpe;
}

int main() {
    static int k,cst,su;
    scanf("%d%d",&n,&m) , Flow::st = n * m * 2 + 1 , Flow::ed = Flow::st + 1;
    for(int i=1,t;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&t) , Flow::singledge(cov(i,j,0),cov(i,j,1),1,t);
    scanf("%d",&k);
    for(int i=1,a,b,c,d;i<=k;i++) scanf("%d%d%d%d",&a,&b,&c,&d) , Flow::singledge(cov(a,b,1),cov(c,d,0),1,0) , Flow::singledge(cov(c,d,1),cov(a,b,0),1,0);
    scanf("%d",&k);
    for(int i=1,a,b;i<=k;i++) scanf("%d%d",&a,&b) , Flow::singledge(Flow::st,cov(a,b,0),1,0);
    for(int i=1,a,b;i<=k;i++) scanf("%d%d",&a,&b) , Flow::singledge(cov(a,b,1),Flow::ed,1,0);
    Flow::flow(cst,su);
    if( su != k ) puts("-1");
    else printf("%d\n",cst);
    return 0;
}
