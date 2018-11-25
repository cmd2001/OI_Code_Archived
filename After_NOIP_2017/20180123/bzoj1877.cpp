#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define bool unsigned char
using namespace std;
const int maxn=4e2+1e1,maxm=4e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<3],nxt[maxm<<3],f[maxm<<3],c[maxm<<3];
int dis[maxn],sou[maxn];
int st,ed;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline void doubledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,flow,cost);
}

inline bool spfa() {
    static bool inq[maxn];
    memset(dis,0x3f,sizeof(dis)); dis[st] = 0;
    queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
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
inline int flow(int& f) {
    int ret = 0 , t = 0; f = 0;
    while( spfa() ) {
        t = release();
        ret += dis[ed] * t , f += t;
    }
    return ret;
}

inline int cov(int p,int s) {
    return ( p << 1 ) + s - 1;
}
int main() {
    static int n,m,f,ans;
    scanf("%d%d",&n,&m);
    st = ( n << 1 ) + 1 , ed = st + 1;
    
    for(int i=1;i<=n;i++)
        doubledge(cov(i,0),cov(i,1),1,0);
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l);
        if( a == 1 && b == n ) singledge(cov(a,1),cov(b,0),1,l);
        else singledge(cov(a,1),cov(b,0),inf,l);
    }
    singledge(st,cov(1,1),inf,0) , singledge(cov(n,0),ed,inf,0);
    
    ans = flow(f);
    
    printf("%d %d\n",f,ans);
    
    return 0;
}

