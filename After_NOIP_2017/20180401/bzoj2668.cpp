#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1.2e3+1e1,maxe=maxn<<6,maxl=25;
const int dx[]={0,0,1,-1,1,1,-1,-1},dy[]={1,-1,0,0,1,-1,1,-1};
const int inf=0x3f3f3f3f;

char ini[maxl][maxl],tar[maxl][maxl],lim[maxl][maxl];
int s[maxn],t[maxe],nxt[maxe],f[maxe],c[maxe];
int dis[maxn],sou[maxn],inq[maxn],st,ed;
int n,m,ans,fullini,fulltar;

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
    int ret = 0 , now = 0 , ff = 0;
    while( spfa() ) {
        ret += dis[ed] * ( now = release() ) ,
        ff += now;
    }
    return ff == fullini ? ret : -1;
}

inline int cov(int x,int y) {
    return m * --x + y;
}
inline int cov(int x,int y,int tpe) { // 1 in , 2 mid , 3 out .
    return cov(x,y) * 3 - 3 + tpe;
}
inline void build(int x,int y) {
    const int in = cov(x,y,1) , mid = cov(x,y,2) , out = cov(x,y,3);
    if( ini[x][y] == 0 && tar[x][y] == 1 ) // more out .
        singledge(in,mid,lim[x][y]>>1,0) , singledge(mid,out,(lim[x][y]+1)>>1,0);
    else if( ini[x][y] == 1 && tar[x][y] == 0 ) // more in .
        singledge(in,mid,(lim[x][y]+1)>>1,0) , singledge(mid,out,lim[x][y]>>1,0);
    else singledge(in,mid,lim[x][y]>>1,0) , singledge(mid,out,lim[x][y]>>1,0);
    if( ini[x][y] == 0 ) singledge(st,mid,1,0) , ++fullini;
    if( tar[x][y] == 0 ) singledge(mid,ed,1,0) , ++fulltar;
    #define legal(a,b) ( 0 < a && a <= n && 0 < b && b <= m )
    for(int k=0;k<8;k++) {
        const int tx = x + dx[k] , ty = y + dy[k];
        if( legal(tx,ty) ) singledge(out,cov(tx,ty,1),inf,1);
    }
}

inline void readarr(char dst[maxl][maxl]) {
    for(int i=1;i<=n;i++) {
        scanf("%s",dst[i]+1);
        for(int j=1;j<=m;j++) dst[i][j] -= '0';
    }
}

int main() {
    scanf("%d%d",&n,&m) , st = n * m * 3 + 1 , ed = st + 1;
    readarr(ini) , readarr(tar) , readarr(lim);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            build(i,j);
    if( fullini != fulltar ) return puts("-1"),0;
    ans = flow();
    printf("%d\n",ans);
    return 0;
}
