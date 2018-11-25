#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
using namespace std;
const int maxn=2e4+1e2,maxm=2e5+1e2;
const int inf=0x3f3f3f3f;

int a[maxm],b[maxm],val[maxm];
int s[maxn],t[maxm<<1],nxt[maxm<<1],f[maxm<<1],cnt=1;
int dep[maxn];
int st,ed;

inline void coredge(int from,int to,int flow) {
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,flow);
}
inline bool bfs() {
    memset(dep,-1,sizeof(dep)); dep[st] = 0;
    queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && !~dep[t[at]] ) {
                dep[t[at]] = dep[pos] + 1 ,
                q.push(t[at]);
            }
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
    return ret;
}

inline void reset() {
    memset(s,0,sizeof(s));
    cnt = 1;
}

inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=getchar()) )
        fix = ch == '-' ? -1 : fix;
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret * fix;
}

int main() {
    static int n,m,w,ans;
    n = getint() , m = getint();
    for(int i=1;i<=m;i++)
        a[i] = getint() , b[i] = getint() , val[i] = getint();
    st = getint() , ed = getint() , w = getint();
    
    for(int i=1;i<=m;i++)
        if( val[i] < w )
            doubledge(a[i],b[i],1);
    ans = dinic();
    
    reset();
    for(int i=1;i<=m;i++)
        if( val[i] > w )
            doubledge(a[i],b[i],1);
    ans += dinic();
    
    printf("%d\n",ans);
    
    return 0;
}


