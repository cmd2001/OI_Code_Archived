#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e2+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<5],nxt[maxn<<5],f[maxn<<5],c[maxn<<5];
int dis[maxn],sou[maxn],inq[maxn],st,ed;

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
    for(int i=ed;i!=st;i=t[sou[i]^1]) ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1]) f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int flow() {
    int ret = 0;
    while( spfa() ) {
        ret += dis[ed] * release();
    }
    return ret;
}

int main() {
    static int n,m,s;
    scanf("%d%d%d",&n,&m,&s) , st = n + 1 , ed = n + 2;
    for(int i=1,u;i<=n;i++) {
        scanf("%d",&u) , singledge(i,ed,u,0);
        if( i != n ) singledge(i,i+1,s,m);
    }
    for(int i=1,d;i<=n;i++) scanf("%d",&d) , singledge(st,i,inf,d);
    printf("%d\n",flow());
    return 0;
}