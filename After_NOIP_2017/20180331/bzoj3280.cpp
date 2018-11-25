#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;


int s[maxn],t[maxe<<5],nxt[maxe<<5],f[maxe<<5],c[maxe<<5],cnt=1;
int dis[maxn],inq[maxn],ins[maxn],st,ed,ans,tar;

inline void coredge(int from,int to,int flow,int cost) {
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
                dis[t[at]] = dis[pos] + c[at];
                if( !inq[t[at]] ) q.push(t[at]);
            }
    }
    return dis[ed] != inf;
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    ins[pos] = 1;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dis[t[at]] == dis[pos] + c[at] && !ins[t[at]] ) {
            now = dfs(t[at],min(flow,f[at]));
            ret += now , flow -= now , ans += c[at] * now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ins[pos]=0,ret;
        }
    if( !ret ) dis[pos] = -1;
    return ins[pos]=0,ret;
}
inline int flow() {
    int ret = 0 , now = 0;
    while( spfa() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    return ret;
}
inline void reset() {
    memset(s,0,sizeof(s)) , cnt = 1;
    tar = 0 , ans = 0;
}

int main() {
    static int T,n,m,k;
    scanf("%d",&T);
    for(int TT=1;TT<=T;TT++) {
        scanf("%d%d%d",&n,&m,&k) , reset() , st = n * 2 + m + 1 , ed = st + 1;
        #define cov(x,tpe) ((x)*2-1+tpe)
        #define cou(x) ((n<<1)+x)
        for(int i=1,a;i<=n;i++) {
            scanf("%d",&a) , tar += a ,
            singledge(cov(i,0),ed,a,0) ,
            singledge(st,cov(i,1),a,0) ;
            if( i != n ) singledge(cov(i,0),cov(i+1,0),inf,0);
        }
        for(int i=1,l,p;i<=m;i++) {
            scanf("%d%d",&l,&p) , singledge(st,cou(i),l,0);
            for(int j=1;j<=n;j++) singledge(cou(i),cov(j,0),inf,p);
        }
        for(int i=1,d,q;i<=k;i++) {
            scanf("%d%d",&d,&q) , ++d;
            for(int j=1;j+d<=n;j++) singledge(cov(j,1),cov(j+d,0),inf,q);
        }
        if( flow() != tar ) printf("Case %d: impossible\n",TT);
        else printf("Case %d: %d\n",TT,ans);
    }
    return 0;
}
