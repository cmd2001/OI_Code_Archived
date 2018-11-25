#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
#define int long long
typedef long long lli;
using namespace std;
const int maxn=1e3+1e2,maxe=1e7+1e2;
const int int_inf=0x3f3f3f3f3f3f3f3fll;
const lli lli_inf=0x3f3f3f3f3f3f3f3fll;

int n,m,e;

namespace Flow {
    int s[maxn],t[maxe],nxt[maxe],f[maxe],c[maxe];
    int inq[maxn],ins[maxn],sou[maxn],st,ed;
    lli dis[maxn],ans;
    inline void coredge(int from,int to,int flow,int cost) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , c[cnt] = cost , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow,int cost) {
        coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
    }
    inline bool spfa() {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        std::queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at]) {
                if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                    dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                    if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
                }
            }
        }
        return dis[ed] != lli_inf;
    }
    inline void release() {
        ans += dis[ed];
        for(int i=ed;i!=st;i=t[sou[i]^1]) f[sou[i]] -= 1 , f[sou[i]^1] += 1;
    }
    inline void flow() {
        while( spfa() ) {
            if( dis[ed] >= 0 ) return;
            release();
        }
    }
    inline int findtar(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( !f[at] && t[at] != st ) return t[at] - n;
        return 0;
    }
}
using namespace Flow;

signed main() {
    scanf("%lld%lld%lld",&n,&m,&e) , st = n + m + 1 , ed = st + 1;
    #define cov(x) (x+n)
    for(int i=1;i<=n;i++) singledge(st,i,1,0);
    for(int i=1;i<=m;i++) singledge(cov(i),ed,1,0);
    for(int i=1,a,b,v;i<=e;i++) scanf("%lld%lld%lld",&a,&b,&v) , singledge(a,cov(b),1,-v);
    flow() , printf("%lld\n",-ans);
    for(int i=1;i<=n;i++) printf("%lld%c",findtar(i),i!=n?' ':'\n');
    return 0;
}
