#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e3+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

int s[maxn],t[maxn<<5],nxt[maxn<<5];
lli c[maxn<<5],f[maxn<<5];
lli dis[maxn];
int sou[maxn],inq[maxn];
int in[maxn],st,ed;

inline void coredge(int from,int to,int cost,int flow) {
    static int cnt = 1;
    t[++cnt] = to , c[cnt] = cost , f[cnt] = flow,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int from,int to,int cost,int flow) {
    coredge(from,to,cost,flow);
    coredge(to,from,-cost,0);
}

inline bool spfa() {
    memset(dis,0x3f,sizeof(dis));
    dis[st] = 0;
    queue<int> q;
    q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]]  = dis[pos] + c[at];
                sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    q.push(t[at]);
                    inq[t[at]] = 1;
                }
            }
    }
    return dis[ed] != inf;
}
inline lli release() {
    lli ret = inf;
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline lli getans() {
    lli ret = 0 , cost = 0 , flow = 0;
    while( spfa() ) {
        cost = dis[ed];
        flow = release();
        ret += cost * flow;
    }
    return ret;
}

inline int cov(int id,int sta) { // 0 means clean , 1 means dirty.
    return ( id << 1 ) - 1 + sta;
}

int main() {
    static int t,p,m,f,n,s;
    scanf("%d%d%d%d%d%d",&t,&p,&m,&f,&n,&s);
    st = t * 2 + 1 , ed = t * 2 + 2;
    for(int i=1;i<=t;i++)
        scanf("%d",in+i);
    for(int i=1;i<=t;i++) {
        addedge(st,cov(i,0),p,in[i]);
        addedge(st,cov(i,1),0,in[i]);
        addedge(cov(i,0),ed,0,in[i]);
        if( i + m <= t )
            addedge(cov(i,1),cov(i+m,0),f,inf);
        if( i + n <= t )
            addedge(cov(i,1),cov(i+n,0),s,inf);
        if( i + 1 <= t )
            addedge(cov(i,1),cov(i+1,1),0,inf);
    }
    
    printf("%lld\n",getans());
    
    return 0;
}
