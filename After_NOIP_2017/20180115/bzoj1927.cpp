#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e3+1e2,maxm=2e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<3],nxt[maxm<<3];
lli f[maxm<<3],c[maxm<<3];
lli dis[maxn];
int sou[maxn];
char inq[maxn];
int st,ed;
int n,m;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    //debug<<"from = "<<from<<"to = "<<to<<"flow = "<<flow<<"cost = "<<cost<<endl;
    coredge(from,to,flow,cost);
    coredge(to,from,0,-cost);
}

inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)); dis[st] = 0;
    queue<int> q; q.push(st); inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        //debug<<"pos = "<<pos<<"dis = "<<dis[pos]<<endl;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at];
                sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    q.push(t[at]), inq[t[at]] = 1;
                }
            }
    }
    //debug<<"dis = "<<dis[ed]<<endl;
    return dis[ed] != 0x3f3f3f3f3f3f3f3fLL;
}
inline lli release() {
    lli ret = inf;
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1]) {
        //debug<<pos<<" ";
        ret = min( ret , f[sou[pos]] );
    }
    //debug<<endl;
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1])
        f[sou[pos]] -= ret , f[sou[pos]^1] += ret;
    return ret;
}
inline lli flow() {
    lli ret = 0;
    while( spfa() )
        ret += dis[ed] * release();
    return ret;
}

inline int cov(int x,int sta) {
    return ( x << 1 ) - 1 + sta;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    st = n * 2 + 1 , ed = n * 2 + 2 ;
    
    for(int i=1;i<=n;i++) {
        singledge(cov(i,1),ed,1,0);
        singledge(st,cov(i,0),1,0);
    }
    for(int i=1,v;i<=n;i++) {
        scanf("%d",&v);
        singledge(st,cov(i,1),1,v);
    }
    for(int i=1,a,b,len;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&len);
        if( a > b ) swap(a,b);
        singledge(cov(a,0),cov(b,1),1,len);
    }
    
    printf("%lld\n",flow());
    
    return 0;
}