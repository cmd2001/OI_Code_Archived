#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define debug cout
using namespace std;
const int maxn=5e2+1e1,maxm=5e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<2],nxt[maxm<<2],f[maxm<<2];
int dep[maxn];
int n,m,st,ed,sum;

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
    if( ! ret )
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

inline void print(int pos) {
    vector<int> vec;
    for(int at=s[pos];at;at=nxt[at])
        if( !f[at] && t[at] != st )
            vec.push_back(t[at]-n);
    if( !vec.size() ) {
        putchar('\n');
        return;
    }
    sort(vec.begin(),vec.end());
    for(unsigned i=0;i<vec.size();i++)
        printf("%d%c",vec[i],i!=vec.size()-1?' ':'\n');
}

int main() {
    scanf("%d%d",&n,&m);
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1,v;i<=n;i++) {
        scanf("%d",&v);
        sum += v;
        addedge(st,i,v);
    }
    for(int i=1,v;i<=m;i++) {
        scanf("%d",&v);
        addedge(i+n,ed,v);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            addedge(i,j+n,1);
    
    if( sum != dinic() )
        return puts("0"),0;
    puts("1");
    for(int i=1;i<=n;i++)
        print(i);
    
    return 0;
}