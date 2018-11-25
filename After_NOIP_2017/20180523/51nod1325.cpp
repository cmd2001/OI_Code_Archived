#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e1+1e2,maxe=1e2+1e1;
const int inf=0x3f3f3f3f;

namespace NetworkFlow {
    int s[maxn],t[maxe<<4],nxt[maxe<<4],f[maxe<<4],cnt;
    int dep[maxn],st,ed;

    inline void coredge(int from,int to,int flow) {
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
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
                now = dfs(t[at],min(flow,f[at])) ,
                ret += now , flow -= now , f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , cnt = 1;
    }
}

struct Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
    inline void coredge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        //debug<<"a = "<<a<<"b = "<<b<<endl;
        coredge(a,b) , coredge(b,a);
    }
    inline void dfs(int pos,int fa) {
        if( ~fa ) NetworkFlow::singledge(pos,fa,inf);
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dfs(t[at],pos);
    }
}t1,t2;

int in[maxn],n,ans;

inline int calc(int cent) {
    using namespace NetworkFlow;
    reset() , st = n + 1 , ed = n + 2;
    int ret = in[cent];
    if( in[cent] > 0 ) singledge(st,cent,inf);
    else singledge(cent,ed,inf);
    for(int i=1;i<=n;i++) {
        if( i == cent ) continue;
        if( in[i] > 0 ) ret += in[i] , singledge(st,i,in[i]);
        else singledge(i,ed,-in[i]);
    }
    t1.dfs(cent,-1) , t2.dfs(cent,-1);
    ret -= dinic();
    return ret;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , t1.addedge(++a,++b);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , t2.addedge(++a,++b);
    for(int i=1;i<=n;i++) ans = max( ans , calc(i) );
    //ans = calc(4);
    printf("%d\n",ans);
    return 0;
}
