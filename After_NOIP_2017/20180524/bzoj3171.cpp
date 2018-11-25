#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=5e2+1e1,maxe=1e3+1e2,maxl=19;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
const int inf=0x3f3f3f3f;

char in[maxl][maxl];
int ix[maxl][maxl],iy[maxl][maxl],n,m,ans;

namespace NetworkFlow {
    int s[maxn],t[maxe<<4],nxt[maxe<<4],f[maxe<<4],c[maxe<<4];
    int dis[maxn],inq[maxn],ins[maxn],st,ed;
    inline void coredge(int from,int to,int flow,int cost) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , c[cnt] = cost , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow,int cost) {
        coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
    }
    inline bool spfa() {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        queue<int> q; q.push(st) , inq[st] = 0;
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
        ins[pos] = 1;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && !ins[t[at]] && dis[t[at]] == dis[pos] + c[at] ) {
            now = dfs(t[at],min(flow,f[at])) , ans += now * c[at] ,
            ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ins[pos] = 0 , ret;
        }
        if( !ret ) dis[pos] = inf;
        return ins[pos] = 0 , ret;
    }
    inline void flow() {
        while( spfa() ) dfs(st,inf);
    }
}

inline int cov(int x,int y,int tpe) {
    int id = m * --x + y;
    return ( id << 1 ) - 1 + tpe;
}
inline int gdx(const char &c) {
    if( c == 'L' || c == 'R' ) return 0;
    return c == 'U' ? -1 : 1;
}
inline int gdy(const char &c) {
    if( c == 'U' || c == 'D' ) return 0;
    return c == 'L' ? -1 : 1;
}
inline void build() {
    using namespace NetworkFlow;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int k=0;k<4;k++) {
        int tx = i + dx[k] , ty = j + dy[k];
        if( tx < 1 ) tx = n;
        if( tx > n ) tx = 1;
        if( ty < 1 ) ty = m;
        if( ty > m ) ty = 1;
        singledge(cov(i,j,0),cov(tx,ty,1),1,dx[k]!=ix[i][j]||dy[k]!=iy[i][j]);
    }
    st = n * m * 2 + 1 , ed = st + 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) singledge(st,cov(i,j,0),1,0) , singledge(cov(i,j,1),ed,1,0);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=m;j++) ix[i][j] = gdx(in[i][j]) , iy[i][j] = gdy(in[i][j]);
    }
    build() , NetworkFlow::flow() , printf("%d\n",ans);
    return 0;
}
