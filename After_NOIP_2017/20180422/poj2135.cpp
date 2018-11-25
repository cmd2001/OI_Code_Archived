#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=1e3+1e2,maxe=1e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2],c[maxe<<2],cnt;
int dis[maxn],sou[maxn],inq[maxn],st,ed;

inline void coredge(int from,int to,int flow,int cost) {
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline void doubledge(int from,int to,int flow,int cost) {
    singledge(from,to,flow,cost) , singledge(to,from,flow,cost);
}
inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
    std::queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]);
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
    int ret = 0 , flw = 0;
    while( spfa() ) ret += dis[ed] * release() , ++flw;
    if( flw < 2 ) return -1;
    return ret;
}

int main() {
    static int n,m;
    while( scanf("%d%d",&n,&m) == 2 ) {
        memset(s,0,sizeof(s)) , cnt = 1 , st = n + 1 , ed = n + 2;
        for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , doubledge(a,b,1,l);
        singledge(st,1,2,0) , singledge(n,ed,2,0);
        printf("%d\n",flow());
    }
    return 0;
}
