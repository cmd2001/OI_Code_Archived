#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=2e2+1e1,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],c[maxe<<1];
int bkf[maxe<<1];
int dis[maxn],sou[maxn],inq[maxn];
int pir[maxn];
int n,st,ed;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa(int ban) {
    for(int i=1;i<=ed;i++) dis[i] = -inf;
    dis[st] = 0;
    queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) {
            if( at!=ban && f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
        }
    }
    return dis[ed] != -inf;
}
inline int release() {
    int ret = inf;
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int getans(int ban) {
    int ret = 0;
    while( spfa(ban) ) {
        ret += dis[ed] * release();
    }
    return ret;
}
inline void getpir() {
    for(int i=1;i<=n;i++)
        for(int at=s[i];at;at=nxt[at])
            if( !f[at] && t[at] != st ) {
                pir[i] = at;
                break;
            }
}
inline int covr(int id) {
    return id + n;
}

int main() {
    static int ans,now;
    scanf("%d",&n) , st = ( n << 1 ) + 1 , ed = st + 1;
    for(int i=1,p;i<=n;i++)
        for(int j=1;j<=n;j++) {
            scanf("%d",&p);
            singledge(i,covr(j),1,p);
        }
    for(int i=1;i<=n;i++) singledge(st,i,1,0) , singledge(covr(i),ed,1,0);
    memcpy(bkf,f,sizeof(f));
    ans = getans(-1);
    getpir();
    printf("%d\n",ans);
    for(int i=1;i<=n;i++) {
        memcpy(f,bkf,sizeof(f));
        now = getans(pir[i]);
        if( now < ans ) printf("%d %d\n",i,t[pir[i]]-n);
    }
    return 0;
}
