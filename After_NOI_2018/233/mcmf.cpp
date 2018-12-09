#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn = 5e3 + 1e2, maxe = 5e4 + 1e2;
const int inf = 0x3f3f3f3f;

int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],c[maxe<<1],dis[maxn],sou[maxn],st,ed,sa,sf;
bool inq[maxn];

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to, f[cnt] = flow, c[cnt] = cost, nxt[cnt] = s[from], s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost), coredge(to,from,0,-cost);
}
inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)), dis[st] = 0;
    queue<int> q; q.push(st), inq[st] = 1;
    while(q.size()) {
        const int pos = q.front(); q.pop(), inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) if(f[at] && dis[t[at]] > dis[pos] + c[at]) {
            dis[t[at]] = dis[pos] + c[at], sou[t[at]] = at;
            if(!inq[t[at]]) q.push(t[at]), inq[t[at]] = 1;
        }
    }
    return dis[ed] != inf;
}
inline int release() {
    int ret = inf;
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1]) ret = min(ret,f[sou[pos]]);
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1]) f[sou[pos]] -= ret, f[sou[pos]^1] += ret;
    return ret;
}
inline void work() {
    while(spfa()) {
        int t = release();
        sf += t, sa += t * dis[ed];
    }
}

int main() {
    static int n,m;
    scanf("%d%d%d%d",&n,&m,&st,&ed);
    for(int i=1,a,b,c,f;i<=m;i++) scanf("%d%d%d%d",&a,&b,&f,&c), singledge(a,b,f,c);
    work(), printf("%d %d\n",sf,sa);
    return 0;
}
