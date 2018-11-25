#include<cstdio>
#include<queue>
const int maxn=5e3+1e2,maxe=2e5+1e2;
const int inf=0x3f3f3f3f;

double dis[maxn],lim;
int n,ans;

namespace SPFA {
    int s[maxn],t[maxe],nxt[maxe];
    double l[maxe];
    bool inq[maxn];
    
    inline void addedge(int from,int to,double len) {
        static int cnt = 0;
        t[++cnt] = to , l[cnt] = len ,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void spfa() {
        for(int i=1;i<=n;i++) dis[i] = inf;
        std::queue<int> q;
        q.push(n) , inq[n] = 1 , dis[n] = 0;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at])
                if( dis[t[at]] > dis[pos] + l[at] ) {
                    dis[t[at]] = dis[pos] + l[at];
                    if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
                }
        }
    }
}

namespace Astar {
    int s[maxn],t[maxe],nxt[maxe];
    double l[maxe];
    int tim[maxn];
    
    struct Node {
        double d;
        int p;
        friend bool operator < (const Node &a,const Node &b) {
            return a.d > b.d;
        }
    };
    std::priority_queue<Node> q;
    
    inline void addedge(int from,int to,double len) {
        static int cnt = 0;
        t[++cnt] = to , l[cnt] = len ,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void Astar(int tlim) {
        q.push((Node){dis[1],1});
        while( q.size() ) {
            const Node pos = q.top(); q.pop();
            for(int at=s[pos.p];at;at=nxt[at])
                if( ++tim[t[at]] <= tlim)
                    q.push((Node){pos.d-dis[pos.p]+l[at]+dis[t[at]],t[at]});
            if( pos.p == n ) {
                if( pos.d <= lim ) lim -= pos.d , ++ans;
                else return;
            }
        }
    }
}

int main() {
    static int m;
    static double len;
    scanf("%d%d%lf",&n,&m,&lim);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d%lf",&a,&b,&len);
        SPFA::addedge(b,a,len) , Astar::addedge(a,b,len);
    }
    SPFA::spfa() , Astar::Astar(lim/dis[1]);
    printf("%d\n",ans);
    return 0;
}
