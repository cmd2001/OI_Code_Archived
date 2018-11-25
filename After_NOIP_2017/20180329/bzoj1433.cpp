#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

int stu[maxn],atp[maxn],tmp[maxn],n,tar,f;

namespace Flow {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],dep[maxn],cnt,st,ed;
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
                now = dfs(t[at],min(flow,f[at])) ,
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
        return ret;
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , cnt = 1;
    }
}

inline int cov(int x,int tpe) {
    return ( x * 2 ) - 1 + tpe;
}
int main() {
    static int T;
    scanf("%d",&T);
    while( T-- ) {
        scanf("%d",&n) , Flow::reset() , Flow::st = n * 2 + 1 , Flow::ed = Flow::st + 1;
        for(int i=1;i<=n;i++) {
            scanf("%d",stu+i);
            if( stu[i] ) Flow::singledge(cov(i,1),Flow::ed,1);
        }
        tar = 0;
        for(int i=1;i<=n;i++) {
            scanf("%d",atp+i) , atp[i] ^= 1;
            if( !stu[i] || ( stu[i] && atp[i] ) ) {
                ++tar , Flow::singledge(Flow::st,cov(i,0),1);
            }
        }
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) scanf("%d",tmp+j);
            if( !stu[i] || ( stu[i] && atp[i] ) ) {
                for(int j=1;j<=n;j++)
                    if( tmp[j] ) {
                        Flow::singledge(cov(i,0),cov(j,1),1);
                    }
                if( stu[i] ) Flow::singledge(cov(i,0),cov(i,1),1);
            }
        }
        f = Flow::dinic();
        puts( f == tar ? "^_^" : "T_T" );
    }
    return 0;
}