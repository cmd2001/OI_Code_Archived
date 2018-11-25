#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
const int maxn=1e3+1e2,maxe=1e6+1e3+1e2;
const int inf=0x3f3f3f3f;

int s[maxn<<1],t[maxe<<2],nxt[maxe<<2],f[maxe<<2],c[maxe<<2];
int dis[maxn<<1],inq[maxn<<1],ins[maxn<<1],sou[maxn<<1],st,ed;
int ans,full,a,b;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa() {
    memset(dis,0xef,sizeof(dis)) , dis[st] = 0;
    std::queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return dis[ed] >= 0;
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    ins[pos] = 1;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dis[t[at]] == dis[pos] + c[at] && !ins[t[at]] ) {
            now = dfs(t[at],std::min(flow,f[at])) , full += now * c[at];
            ret += now , flow -= now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) {
                ins[pos] = 0;
                return ret;
            }
        }
    if( !ret ) dis[pos] = -inf;
    ins[pos] = 0;
    return ret;
}

inline int flow() {
    int ret = 0 , now = 0;
    while( spfa() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}

inline int cov(int x,int tpe) { // tpe == 0 means left point , tpe == 1 means right point .
    return ( x - a + 1 ) * 2 - 1 + tpe;
}
inline int gcd(int x,int y) {
    register int t;
    while( t = x % y ) x = y , y = t;
    return y;
}
inline bool can(int x,int y) { // assert x > y .
    int z = sqrt(x*x-y*y);
    if( z * z == x * x - y * y && gcd(y,z) == 1 ) return 1;
    return 0;
}

int main() {
    scanf("%d%d",&a,&b) , st = ( b - a + 1 ) * 2 + 1 , ed = st + 1;
    for(int i=a;i<=b;i++)
        for(int j=a;j<i;j++)
            if( can(i,j) ) {
                singledge(cov(i,0),cov(j,1),1,i+j) ,
                singledge(cov(j,0),cov(i,1),1,i+j) ;
            }
    for(int i=a;i<=b;i++) {
        singledge(st,cov(i,0),1,0) ,
        singledge(cov(i,1),ed,1,0) ;
    }
    ans = flow();
    printf("%d %d\n",ans>>1,full>>1);
    return 0;
}
