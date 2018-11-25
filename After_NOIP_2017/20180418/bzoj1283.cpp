#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<3],nxt[maxn<<3],f[maxn<<3],c[maxn<<3];
int dis[maxn],inq[maxn],ins[maxn],st,ed,ans;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
    queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return dis[ed] != inf;
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0; ins[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && dis[t[at]] == dis[pos] + c[at] && !ins[t[at]] ) {
            now = dfs(t[at],min(flow,f[at])) ,
            ret += now , flow -= now , ans += now * c[at] ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ins[pos] = 0 , ret;
        }
    if( !ret ) dis[pos] = inf;
    return ins[pos] = 0 , ret;
}
inline void flow() {
    while( spfa() ) while( dfs(st,inf) ) ;
}

int main() {
    static int in[maxn],n,m,k;
    scanf("%d%d%d",&n,&m,&k) , st = n - m + 3 , ed = st + 1;
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    singledge(st,1,k,0) , singledge(n-m+2,ed,k,0);
    for(int i=1;i<=n-m+1;i++) singledge(i,i+1,inf,0);
    for(int i=1;i<=n;i++) {
        if( i <= m ) singledge(1,i+1,1,-in[i]);
        else if( i >= n - m + 1 ) singledge(i-m+1,n-m+2,1,-in[i]);
        else singledge(i-m+1,i+1,1,-in[i]);
    }
    flow() , printf("%d\n",-ans);
    return 0;
}