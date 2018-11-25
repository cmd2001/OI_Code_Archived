#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

char buf[1<<20],*at;
int s[maxn<<1],t[maxm<<2],nxt[maxm<<2],f[maxm<<2];
int dep[maxn<<1];
int n,m,st,ed,ans;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int from,int to,int flow) {
    coredge(from,to,flow);
    coredge(to,from,0);
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
                dep[t[at]] = dep[pos] + 1,
                q.push(t[at]);
            }
    }
    return ~dep[ed];
}
inline int dfs(int pos,int flow) {
    //debug<<"pos = "<<pos<<endl;
    if( pos == ed )
        return flow;
    int ret = 0 , now = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at]));
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
        while( now = dfs(st,inf) ) {
            //debug<<"now = "<<now<<endl;
            ret += now;
        }
    }
    //debug<<"ret = "<<ret<<endl;
    return ret;
}

inline int getint(char* &sou) {
    int ret = 0;
    while( !isdigit(*sou) )
        if( *sou == 0  || *sou == '\n' || *sou == '\r' )
            return -1;
        else
            ++sou;
    while( isdigit(*sou) )
        ret = ret * 10 + *sou++ - '0';
    return ret;
}

int main() {
    scanf("%d%d",&n,&m);
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1,d;i<=n;i++) {
        fgets(at=buf,sizeof(buf),stdin);
        while( !isdigit(*buf) )
            fgets(buf,sizeof(buf),stdin);
        ans += ( d = getint(at) );
        addedge(st,i,d);
        while( ~ ( d = getint(at) ) )
            addedge(i,d+n,inf);
    }
    for(int i=1,d;i<=m;i++) {
        //debug<<"i = "<<i<<endl;
        scanf("%d",&d);
        addedge(i+n,ed,d);
    }
    
    ans -= dinic();
    
    for(int i=1;i<=n;i++)
        if( ~dep[i] )
            printf("%d ",i);
    putchar('\n');
    for(int i=1;i<=m;i++)
        if( ~dep[i+n] )
            printf("%d ",i);
    putchar('\n');
    
    printf("%d\n",ans);
    
    return 0;
}
