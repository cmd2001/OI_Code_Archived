#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=2e2+1e1,maxe=1e4+1e2;
const int int_inf=0x3f3f3f3f;
const lli lli_inf=0x3f3f3f3f3f3f3f3fll;

int s[maxn],t[maxe<<4],nxt[maxe<<4],f[maxe<<4],cnt=1;
lli c[maxe<<4],dis[maxn];
int sou[maxn],inq[maxn];
int st,ed,_s,_t;

inline void coredge(int from,int to,int flow,int cost) {
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
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return dis[ed] != lli_inf;
}
inline int release() {
    int ret = int_inf;
    for(int i=ed;i!=st;i=t[sou[i]^1]) ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1]) f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline lli flow() {
    lli ret = 0;
    while( spfa() ) ret += dis[ed] * release();
    return ret;
}

inline int cov(int x,int tpe) { // 0 means in point , 1 meams out point .
    return x * 2 - 1 + tpe;
}

int main() {
    static int n,k;
    scanf("%d%d",&n,&k) , _s = n * 2 + 1 , _t = _s + 1 , st = _t + 1 , ed = st + 1;
    singledge(_t,_s,k,0);
    for(int i=1,w;i<=n;i++) {
        scanf("%d",&w) , singledge(_s,cov(i,0),1,w) , singledge(cov(i,1),_t,1,0) ,
        singledge(cov(i,0),ed,1,0) , singledge(st,cov(i,1),1,0);
    }
    for(int i=1,w;i<n;i++) for(int j=i+1;j<=n;j++) {
        scanf("%d",&w) , singledge(cov(i,1),cov(j,0),1,w);
    }
    printf("%lld\n",flow());
    
    return 0;
}
