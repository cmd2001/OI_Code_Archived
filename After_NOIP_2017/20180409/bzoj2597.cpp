#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=6e3+1e1,maxp=1e2+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<5],nxt[maxn<<5],f[maxn<<5],c[maxn<<5];
int dis[maxn],inq[maxn],ins[maxn],st,ed;
int id[maxp][maxp],ans[maxp][maxp],in[maxp][maxp],su,cont,full;
int n;

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
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
            dis[t[at]] = dis[pos] + c[at];
            if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
        }
    }
    return dis[ed] != inf;
}
inline int dfs(int pos,int flow) {
    if( pos == ed ) return flow;
    int ret = 0 , now = 0;
    ins[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( f[at] && !ins[t[at]] && dis[t[at]] == dis[pos] + c[at] ) {
            now = dfs(t[at],min(flow,f[at])) ,
            ret += now , flow -= now , full += c[at] * now ,
            f[at] -= now , f[at^1] += now;
            if( !flow ) return ins[pos] = 0 , ret;
        }
    if( !ret ) dis[pos] = inf;
    return ins[pos] = 0 , ret;
}
inline int flow() {
    while( spfa() ) dfs(st,inf);
    return full;
}

inline int cc(int x) {
    return x * ( x - 1 ) * ( x - 2 ) / 6;
}
inline int findtar(int pos) {
    for(int at=s[pos];at;at=nxt[at]) if( !f[at] ) return t[at];
    
}
inline void getid() {
    st = n + 1 , su = ed = n + 2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            id[i][j] = ++su;
}
inline void getans() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++) {
            const int tar = findtar(id[i][j]);
            if( tar == i ) ans[i][j] = 1 , ans[j][i] = 0;
            else ans[i][j] = 0 , ans[j][i] = 1;
        }
}

int main() {
    scanf("%d",&n) , getid();
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",in[i]+j);
    for(int i=1;i<=n;i++) for(int j=1;j<i;j++) {
        singledge(st,id[i][j],1,0);
        if( in[i][j] == 0 ) singledge(id[i][j],j,1,0);
        else if( in[i][j] == 1 ) singledge(id[i][j],i,1,0);
        else singledge(id[i][j],i,1,0) , singledge(id[i][j],j,1,0);
    }
    for(int i=1;i<=n;i++) for(int j=0;j<n;j++) singledge(i,ed,1,j);
    printf("%d\n",cc(n)-flow()) , getans();
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) printf("%d%c",ans[i][j],j!=n?' ':'\n');
    }
    return 0;
}
