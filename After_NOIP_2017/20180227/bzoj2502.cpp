#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2],cnt=1;
int dep[maxn],deg[maxn];
int baks[maxn],bakcnt;
int st,ed,_s,_t;

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
}
inline bool bfs() {
    memset(dep,-1,sizeof(dep)) , dep[st] = 0;
    queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] )
                dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at]));
            ret += now , flow -= now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
    if( !ret ) dep[pos] = -1;
    return ret;
}
inline int dinic() {
    int ret = 0 , now = 0;
    while( bfs() ) {
        while( now = dfs(st,inf) )
            ret += now;
    }
    //cerr<<"ret = "<<ret<<endl;
    return ret;
}

inline void backup() {
    memcpy(baks,s,sizeof(s)) , bakcnt = cnt;
}
inline void restore() {
    memcpy(s,baks,sizeof(s)) , cnt = bakcnt;
}

inline int findflow() {
    for(int at=s[_s];at;at=nxt[at])
        if( t[at] == _t ) return f[at];
    throw "It shouldn't be here";
}


int main() {
    static int n,ans;
    scanf("%d",&n) , _s = n + 1 , _t = _s + 1 , st = _t + 1 , ed = st + 1;
    for(int i=1,t,x;i<=n;i++) {
        scanf("%d",&t);
        while( t-- ) {
            scanf("%d",&x);
            ++deg[i] , --deg[x];
            singledge(i,x,inf);
        }
        singledge(_s,i,inf) , singledge(i,_t,inf);
    }
    backup();
    singledge(_t,_s,inf);
    for(int i=1;i<=n;i++) {
        if( deg[i] > 0 ) singledge(i,ed,deg[i]);
        else singledge(st,i,-deg[i]);
    }
    dinic() , ans = findflow();
    restore();
    st = _t , ed = _s;
    ans -= dinic();
    printf("%d\n",ans);
    return 0;
}

