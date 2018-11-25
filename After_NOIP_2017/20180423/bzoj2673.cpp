#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=1e2+1e1,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

char in[maxn][maxn];
int s[maxn],t[maxe<<3],nxt[maxe<<3],f[maxe<<3],c[maxe<<3],cnt;
int dis[maxn],inq[maxn],ins[maxn],st,ed,cst;
int sx[maxn],sy[maxn],su,ini;
int n,A,B,ans;

inline void coredge(int from,int to,int flow,int cost) {
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
                dis[t[at]] = dis[pos] + c[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return dis[ed] != inf;
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0; ins[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && !ins[t[at]] && dis[t[at]] == dis[pos] + c[at] ) {
            now = dfs(t[at],std::min(flow,f[at])) ,
            ret += now , flow -= now , cst += c[at] * now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ins[pos] = 0 , ret;
        }
    if( !ret ) dis[pos] = inf;
    return ins[pos] = 0 , ret;
}
inline int flow() { // we must got full flow .
    int ret = 0 , now = 0;
    while( spfa() ) while( ( now = dfs(st,inf) ) ) ret += now;
    return ret;
}

inline void build(int t) {
    memset(s,0,sizeof(s)) , cnt = 1 , st = n * 2 + 1 , ed = st + 1 , cst = 0;
    #define cov(x,id) (x*2-1+id)
    for(int i=1;i<=n;i++) {
        singledge(st,cov(i,0),sx[i],0) ,
        singledge(cov(i,0),cov(i,1),t,0) ,
        singledge(cov(i,1),ed,sy[i],0) ;
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if( in[i][j] == '.' ) singledge(cov(i,0),cov(j,1),1,1);
}
inline int calc(int t) {
    build(t);
    if( flow() != su ) return -1; // illegal .
    int used = su - cst;
    return used * A >= t * B ? used - ini : -1;
}

int main() {
    static int cse;
    while( scanf("%d%d%d",&n,&A,&B) == 3 && ( n || A || B ) ) {
        memset(sx,0,sizeof(sx)) , memset(sy,0,sizeof(sy)) , ini = su = 0 , ans = -1;
        for(int i=1;i<=n;i++) {
            scanf("%s",in[i]+1);
            for(int j=1;j<=n;j++){
                if( in[i][j] != '/' ) ++sx[i] , ++sy[j] , ++su;
                ini += in[i][j] == 'C';
            }
        }
        for(int i=0;i<=n;i++) ans = std::max( ans , calc(i) );
        printf("Case %d: ",++cse);
        if( !~ans ) puts("impossible");
        else printf("%d\n",ans);
    }
    return 0;
}

