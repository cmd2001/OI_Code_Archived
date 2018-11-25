#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e2+1e1,maxe=7e2+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],dep[maxn];
int st,ed;

inline int cov(char x) {
    return x <= 'z' && x >= 'a' ? x - 'a' + 1 : x - 'A' + 27;
}

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
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
    return ret;
}

int main() {
    static int n;
    static char l[10],r[10];
    scanf("%d",&n) , st = cov('A') , ed = cov('Z');
    for(int i=1,f;i<=n;i++) {
        scanf("%s%s%d",l,r,&f) ,
        singledge(cov(*l),cov(*r),f);
    }
    printf("%d\n",dinic());
    return 0;
}
