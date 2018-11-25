#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxe=5e5+1e2;
const int inf=0x3f3f3f3f;

int n,m;
int s[maxn],t[maxe],nxt[maxe],f[maxe],c[maxe];
int dis[maxn],sou[maxn],inq[maxn],ins[maxn],st,ed;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
    queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return dis[ed] != inf;
}
inline int dfs(int pos,int flow,int& ans) {
    if( pos == ed ) return flow;
    ins[pos] = 1;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && !ins[t[at]] && dis[t[at]] == dis[pos] + c[at] ) {
            now = dfs(t[at],min(flow,f[at]),ans);
            ret += now , flow -= now , ans += c[at] * now ;
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ins[pos] = 0 , ret;
        }
    if( !ret ) dis[pos] = inf;
    return ins[pos] = 0 , ret;
}
inline int flow() {
    int ret = 0;
    while( spfa() ) while( dfs(st,inf,ret) );
    return ret;
}

inline bool ned(int x) {
    if( x == 0 || x == 5 || x == 10 || x == 15 ) return 0;
    return 1;
}
inline int cov(int x,int dir) { // dir in range [0,4]
    return ( 5 * --x ) + dir + 1;
}
inline int gid(int x,int y) {
    if( !x || !y || x > n || y > m ) return 0;
    return m * --x + y;
}
inline int cntbit(int x) {
    int ret = 0;
    while(x) ++ret , x -= (x&-x);
    return ret;
}
inline int finddir(int x) {
    #define bit(i) ( x & ( 1 << ( (i) % 4 ) ) )
    if( cntbit(x) == 1 ) {
        for(int i=0;i<4;i++) if( bit(i) ) return i;
    } else if( cntbit(x) == 2 ) {
        for(int i=0;i<4;i++) if( bit(i) && bit(i+1) ) return i;
    } else {
        for(int i=0;i<4;i++) if( bit(i) && bit(i+1) && bit(i+3) ) return i;
    }
    throw "It shouldn't be here";
}
inline void addedge(int x,int y,int flow,int cost,int tpe) {
    if( tpe ) singledge(x,y,flow,cost);
    else singledge(y,x,flow,cost);
}
inline void buildtube(int pos,int x,int t) {
    const int cent = cov(pos,4);
    if(t) singledge(st,cent,cntbit(x),0);
    else singledge(cent,ed,cntbit(x),0);
    if( !ned(x) ) {
        for(int i=0;i<4;i++) if( x & ( 1 << i ) ) addedge(cent,cov(pos,i),1,0,t);
    } else {
        int dir = finddir(x) , bit = cntbit(x);
        const int a = cov(pos,dir) , b = cov(pos,(dir+1)%4) , c = cov(pos,(dir+2)%4) , d = cov(pos,(dir+3)%4);
        if( bit == 1 ) {
            addedge(cent,a,1,0,t) ,
            addedge(a,b,1,1,t) , addedge(a,c,1,2,t) , addedge(a,d,1,1,t) ;
        } else if( bit == 2 ) {
            addedge(cent,a,1,0,t) , addedge(cent,b,1,0,t) ,
            addedge(a,c,1,1,t) , addedge(b,d,1,1,t) ;
        } else if( bit == 3 ) {
            addedge(cent,d,1,0,t) , addedge(cent,a,1,0,t) , addedge(cent,b,1,0,t) ,
            addedge(a,c,1,2,t) , addedge(d,c,1,1,t) , addedge(b,c,1,1,t);
        }
    }
}
inline void buildlnk(int x,int y) {
    static const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
    const int pos = gid(x,y);
    for(int i=0;i<4;i++) {
        const int tar = gid(x+dx[i],y+dy[i]);
        if(tar) singledge(cov(pos,i),cov(tar,(i+2)%4),1,0);
    }
}
inline int getcol(int x,int y) {
    return (x+y)&1;
}

int main() {
    static int w,ans;
    scanf("%d%d",&n,&m) , st = n * m * 5 + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&w) , buildtube(gid(i,j),w,getcol(i,j));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(getcol(i,j)) buildlnk(i,j);
    ans = flow() , printf("%d\n",ans);
    return 0;
}

