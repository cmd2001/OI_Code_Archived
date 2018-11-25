#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=4e2+1e1,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<4],nxt[maxm<<4],f[maxm<<4];
int dep[maxn];
int N,F,D,st,ed;

inline void coredge(int from,int to,int flow) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
    coredge(from,to,flow) , coredge(to,from,0);
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

inline int covmid(int x,int sta) {
    return F + x * 2 - 1 + sta;
}
inline int covr(int x) {
    return F + N * 2 + x;
}

int main() {
    scanf("%d%d%d",&N,&F,&D);
    st = N * 2 + F + D + 1 , ed = st + 1;
    for(int i=1;i<=F;i++)
        singledge(st,i,1);
    for(int i=1,ff,dd,x;i<=N;i++) {
        scanf("%d%d",&ff,&dd);
        singledge(covmid(i,0),covmid(i,1),1);
        while( ff-- ) {
            scanf("%d",&x);
            singledge(x,covmid(i,0),1);
        }
        while( dd-- ) {
            scanf("%d",&x);
            singledge(covmid(i,1),covr(x),1);
        }
    }
    for(int i=1;i<=D;i++)
        singledge(covr(i),ed,1);
    
    printf("%d\n",dinic());
    
    return 0;
}
