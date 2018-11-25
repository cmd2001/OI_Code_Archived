#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define bool unsigned char
using namespace std;
const int maxn=55,maxm=810,maxe=maxm*maxn;
const int inf=0x3f3f3f3f;

namespace Flow {
    int s[maxm],t[maxe<<3],nxt[maxe<<3],f[maxe<<3],c[maxe<<3];
    int dis[maxm],sou[maxm];
    int st,ed;
    
    inline void coredge(int from,int to,int flow,int cost) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , c[cnt] = cost,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow,int cost) {
        coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
    }
    inline bool spfa() {
        static bool inq[maxm];
        for(int i=0;i<=ed;i++) dis[i] = -inf;
        dis[st] = 0;
        queue<int> q; q.push(st); inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop(); inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                    dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                    if( !inq[t[at]] ) {
                        q.push(t[at]) , inq[t[at]] = 1;
                    }
                }
        }
        return dis[ed] > 0;
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
    inline void init(int m) {
        st = m + 1 , ed = m + 2;
    }
}
using Flow::singledge; using Flow::st; using Flow::ed;

int id[maxn][maxn],mrk[maxm],x[maxm],y[maxm],len[maxm];
queue<int> es;
int n,m;

inline bool dfs(int pos,int fa,int tar) {
    if( pos == tar ) return 1;
    for(int i=1;i<=n;i++)
        if( id[pos][i] && mrk[id[pos][i]] && i != fa ) {
            if( dfs(i,pos,tar) ) {
                es.push(id[pos][i]);
                return 1;
            }
        }
    return 0;
}

inline void build(int now) {
    while( es.size() ) {
        const int pos = es.front(); es.pop();
        if( len[pos] > len[now] ) {
            singledge(pos,now,1,len[pos]-len[now]);
        }
    }
}

inline int getint() {
    int ret = 0 , ch ;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    Flow::init(m);
    for(int i=1;i<=m;i++) {
        x[i] = getint() , y[i] = getint() , len[i] = getint();
        id[x[i]][y[i]] = id[y[i]][x[i]] = i;
    }
    for(int i=1;i<n;i++)
        mrk[id[getint()][getint()]] = 1;
    
    for(int i=1;i<=m;i++) {
        if( !mrk[i] ) {
            singledge(i,ed,1,0);
            dfs(x[i],-1,y[i]);
            build(i);
        } else singledge(st,i,1,0);
    }
    
    
    printf("%d\n",Flow::flow());
    
    return 0;
}
