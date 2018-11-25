#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxm=1e4+1e3;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

int in[maxn];
int s[maxn],t[maxm<<4],nxt[maxm<<4];
lli f[maxm<<4],c[maxm<<4];
lli dis[maxn];
int sou[maxn],inq[maxn];
int st,ed;

inline void coredge(int from,int to,lli flow,lli cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,lli flow,lli cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}

inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
    queue<int> q; q.push(st); inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        if( pos == ed ) continue;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    q.push(t[at]) , inq[t[at]] = 1;
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
inline lli flow() {
    lli ret = 0;
    while( spfa() )
        ret += dis[ed] * release();
    return ret;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,m;
    n = getint() , m = getint();
    st = n + 2 , ed = n + 3;
    for(int i=1;i<=n;i++)
        in[i] = getint();
    for(int i=1,a,b,v;i<=m;i++) {
        a = getint() , b = getint() , v = getint();
        ++b;
        singledge(a,b,inf,v);
    }
    for(int i=1;i<=n+1;i++) {
        int d = in[i] - in[i-1];
        if( d > 0 ) singledge(st,i,d,0);
        else if( d < 0 ) singledge(i,ed,-d,0);
        if( i ) singledge(i,i-1,inf,0);
    }
    //debug<<"edge added"<<endl;
    
    printf("%lld\n",flow());
    
    return 0;
}