#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2],c[maxe<<2];
int dis[maxn],inq[maxn],sou[maxn];
int st,ed,_s,_t;

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
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int flow() {
    int ret = 0;
    while( spfa() ) {
        ret += dis[ed] * release();
    }
    return ret;
}
inline int cov(int p,int tpe) { // 0 means in , 1 means out .
    return p * 2 - 1 + tpe;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m) , _s = n * 2 + 1 , _t = _s + 1 , st = _t + 1 , ed = st + 1;
    singledge(_t,_s,m,0);
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x);
        singledge(_s,cov(i,0),inf,0) , singledge(cov(i,1),_t,inf,0) ,
        singledge(st,cov(i,1),x,0) , singledge(cov(i,0),ed,x,0);
    }
    for(int i=1,x;i<=n;i++)
        for(int j=i+1;j<=n;j++) {
            scanf("%d",&x);
            if( ~x ) singledge(cov(i,1),cov(j,0),inf,x);
        }
    printf("%d\n",flow());
    return 0;
}
