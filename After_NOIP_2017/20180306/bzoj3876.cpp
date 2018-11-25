#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=3e2+1e1,maxe=5e3+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<4],nxt[maxe<<4],f[maxe<<4],c[maxe<<4];
int dis[maxn],sou[maxn],inq[maxn],deg[maxn];
int st,ed,_s,_t;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost,bool must=0) {
    if(must) ++deg[from] , --deg[to];
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
inline int flow() {
    int ret = 0;
    while( spfa() ) {
        ret += dis[ed] * release();
    }
    return ret;
}

int main() {
    static int n,ans;
    scanf("%d",&n) , _s = n + 1 , _t = _s + 1 , st = _t + 1 , ed = st + 1;
    singledge(_s,1,inf,0,0);
    for(int i=1,k,b,t;i<=n;i++) {
        scanf("%d",&k);
        while(k--) {
            scanf("%d%d",&b,&t) , ans += t;
            singledge(i,b,inf,t,1);
        }
        if(i-1) singledge(i,_t,inf,0);
    }
    singledge(_t,_s,inf,0,0);
    for(int i=1;i<=n+2;i++)
        if( deg[i] > 0 ) singledge(i,ed,deg[i],0);
        else singledge(st,i,-deg[i],0);
    ans += flow();
    printf("%d\n",ans);
    return 0;
}
