#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=2e3+1e1,maxe=0.8*(maxn*maxn>>1);
const int inf=0x3f3f3f3f;

struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x; 
    }
}ps[maxn];
int s[maxn<<1],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],c[maxe<<1];
int dis[maxn<<1],sou[maxn<<1],inq[maxn<<1];
int n,st,ed;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}

inline bool spfa() {
    memset(dis,-1,sizeof(dis)) , dis[st] = 0;
    queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return ~dis[ed];
}
inline int release() {
    int ret = inf;
    for(int i=ed;i!=st;i=t[sou[i]^1]) ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1]) f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int flow() {
    int ret = 0;
    for(int i=1;i<=2;i++) {
        if( spfa() ) ret += dis[ed] * release();
    }
    return ret;
}

inline int cov(int x,int tpe) {
    return ( x << 1 ) - 1 + tpe;
}
inline void buildp(int x) {
    int miv = inf;
    singledge(cov(x,0),cov(x,1),1,1) ,
    singledge(cov(x,0),cov(x,1),1,0) ;
    for(int i=x+1;i<=n;i++) {
        if( miv <= ps[i].y ) continue;
        if( ps[x].y <= ps[i].y ) {
            singledge(cov(x,1),cov(i,0),2,0);
            miv = min( miv , ps[i].y );
        }
    }
}
inline void build() {
    st = n * 2 + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) singledge(st,cov(i,0),2,0);
    for(int i=1;i<=n;i++) buildp(i);
    for(int i=1;i<=n;i++) singledge(cov(i,1),ed,2,0);
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&ps[i].x,&ps[i].y);
    sort(ps+1,ps+1+n);
    build();
    printf("%d\n",flow());
    return 0;
}

