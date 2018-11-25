#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int maxn=1e3+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<5],nxt[maxn<<5],f[maxn<<5];
int dep[maxn],st=1,ed=2;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
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

inline int gid(const string s) {
    static map<string,int> mp;
    static int iid = 2;
    if( mp.find(s) == mp.end() ) mp[s] = ++iid;
    return mp[s];
}

int main() {
    static int n,m,k;
    static string in,x,y;
    cin >> n;
    for(int i=1;i<=n;i++) cin >> in , singledge(gid(in),ed,1);
    cin >> m;
    for(int i=1;i<=m;i++) cin >> in >> in , singledge(st,gid(in),1);
    cin >> k;
    for(int i=1;i<=k;i++) cin >> x >> y , singledge(gid(x),gid(y),inf);
    printf("%d\n",m-dinic());
    return 0;
}
