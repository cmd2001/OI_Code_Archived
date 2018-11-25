#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=1e3+1e2,maxe=40*maxn,maxl=4e1+5e0,maxr=1e2+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2],c[maxe<<2];
int bel[maxn],pcnt;
int dis[maxn],sou[maxn],inq[maxn];
int in[maxl][maxr],tar[maxl],used[maxr];
int n,m,st,ed,lstp;

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
    lstp = bel[t[sou[ed]^1]];
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = std::min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline void rebuild() {
    ++used[lstp] , bel[++pcnt] = lstp;
    for(int i=1;i<=n;i++) singledge(i+2,pcnt,1,in[i][lstp]*(used[lstp]+1));
    singledge(pcnt,ed,1,0);
}
inline int flow() {
    int ret = 0;
    while( spfa() ) {
        ret += dis[ed] * release();
        rebuild();
    }
    return ret;
}

int main() {
    scanf("%d%d",&n,&m) , st = ++pcnt , ed = ++pcnt;
    for(int i=1;i<=n;i++) {
        scanf("%d",tar+i);
        singledge(st,++pcnt,tar[i],0);
    }
    for(int j=1;j<=m;j++) {
        bel[++pcnt] = j ,singledge(pcnt,ed,1,0);
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            scanf("%d",in[i]+j) , singledge(i+2,n+2+j,1,in[i][j]);
        }
    }
    printf("%d\n",flow());
    return 0;
}
