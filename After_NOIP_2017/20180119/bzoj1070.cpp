#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=6e2+1e1,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<4],nxt[maxm<<4],f[maxm<<4],c[maxm<<4];
int dis[maxn],sou[maxn],inq[maxn];
int n,m,st,ed;
double ans;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa() {
    memset(dis,inf,sizeof(dis)); dis[st] = 0;
    queue<int> q; q.push(st); inq[st] = 0;
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        if( pos == ed ) continue;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    q.push(t[at]) , inq[t[at]] = 1;
                }
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

inline int cov(int per,int tme) {
    return m * --tme + per;
}
inline int covr(int per) {
    return n * m + per;
}

int main() {
    scanf("%d%d",&m,&n);
    st = n * ( m + 1 ) + 1 , ed = n * ( m + 1 ) + 2;
    for(int i=1;i<=m;i++)
        for(int t=1;t<=n;t++)
            singledge(st,cov(i,t),1,0);
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=m;j++) {
            scanf("%d",&x);
            for(int t=1;t<=n;t++)
                singledge(cov(j,t),covr(i),1,t*x);
        }
    for(int i=1;i<=n;i++)
        singledge(covr(i),ed,1,0);
    
    ans = flow();
    printf("%0.2lf\n",ans/n);
    
    return 0;
}