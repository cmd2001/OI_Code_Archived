#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ulli unsigned long long int
#define debug cout
using namespace std;
const int maxn=5e2+1e1,maxm=4e3+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<4],nxt[maxm<<4],f[maxm<<4],cnt;
int dep[maxn];
unsigned int val[maxn];
char vis[maxn];
int xx[maxm],yy[maxm];
int n,m,st,ed,tt;
unsigned ans;

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow);
    coredge(to,from,0);
}
inline void doubledge(int from,int to,int flow) {
    coredge(from,to,flow);
    coredge(to,from,flow);
}

inline bool bfs() {
    memset(dep,-1,sizeof(dep));
    dep[st] = 0;
    queue<int> q;
    q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1;
                q.push(t[at]);
            }
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    if( pos == ed )
        return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(f[at],flow));
            ret += now , flow -= now,
            f[at] -= now , f[at^1] += now;
            if( !flow )
                return ret;
        }
    if( !ret )
        dep[pos] = -1;
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

inline void build(int bit) {
    for(int i=1;i<=n;i++)
        if( vis[i] ) {
            if( ( val[i] >> bit ) & 1u ) {
                singledge(st,i,inf);
            }
            else
                singledge(i,ed,inf);
        }
    for(int i=1;i<=m;i++)
        if( vis[xx[i]] + vis[yy[i]] != 2 )
            doubledge(xx[i],yy[i],1);
}

inline void reset() {
    memset(s,0,sizeof(s));
    cnt = 1;
}

inline void calc(int bit) {
    reset();
    build(bit);
    //cout<<"dinic = "<<dinic()<<endl;
    dinic();
    for(int i=1;i<=n;i++) {
        //debug<<"i = "<<i<<"dep = "<<dep[i]<<endl;
        if( !vis[i] && ~dep[i] )
            val[i] += 1u << bit;
        }
}

int main() {
    scanf("%d%d",&n,&m);
    st = n + 1 , ed = n + 2;
    for(int i=1;i<=m;i++)
        scanf("%d%d",xx+i,yy+i);
    scanf("%d",&tt);
    for(int i=1,p;i<=tt;i++) {
        scanf("%d",&p);
        scanf("%u",val+p);
        vis[p] = 1;
    }
    
    for(int i=0;i<32;i++)
        calc(i);
    
    //debug<<"n = "<<n<<endl;
    for(int i=1;i<=n;i++)
        printf("%u\n",val[i]);
    
    return 0;
}
