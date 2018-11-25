#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=6e3+1e2,maxe=1e3+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<4],nxt[maxn<<4],f[maxn<<4],c[maxn<<4];
int dis[maxn],sou[maxn],inq[maxn];
int full[maxn],won[maxn],che[maxn],C[maxn],D[maxn],u[maxe],v[maxe];
int n,m,st,ed,ans;

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
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return dis[ed] != inf;
}
inline int release() {
    int ret = inf;
    for(int i=ed;i!=st;i=t[sou[i]^1]) {
        ret = min( ret , f[sou[i]] );
    }
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int flow() {
    int ret = 0;
    while( spfa() ) ret += dis[ed] * release();
    return ret;
}
inline void build() {
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1;i<=m;i++) singledge(st,i+n,1,0);
    for(int i=1;i<=m;i++) singledge(i+n,u[i],1,0) , singledge(i+n,v[i],1,0);
    for(int i=1;i<=n;i++) {
        che[i] += won[i];
        for(int t=won[i],cst;t<che[i];t++) {
            cst = C[i] * ( 2 * t + 1 ) + ( - 2 * ( full[i] - t ) + 1 ) * D[i];
            singledge(i,ed,1,cst);
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d%d",won+i,full+i,C+i,D+i) , full[i] += won[i];
    for(int i=1;i<=m;i++) {
        scanf("%d%d",u+i,v+i) , 
        ++full[u[i]] , ++full[v[i]] ,
        ++che[u[i]] , ++che[v[i]];
    }
    for(int i=1;i<=n;i++) ans += C[i] * won[i] * won[i] + D[i] * ( full[i] - won[i] ) * ( full[i] - won[i] );
    build();
    ans += flow();
    printf("%d\n",ans);
    return 0;
}

