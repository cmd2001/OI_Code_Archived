#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define bool unsigned char
typedef long long int lli;
const int maxn=1e5+1e2,maxe=4e5+1e2,maxs=1<<5;

int s[maxn],t[maxe],nxt[maxe];
lli l[maxe],f[maxs][maxn],ans;
bool vis[maxn];
int n,full;

inline void addedge(const int &from,const int &to,const lli &len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
struct Node {
    lli len;
    int pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.len > b.len;
    }
};
std::priority_queue<Node> pq;

inline void dji(lli* dis) {
    for(int i=1;i<=n;i++) pq.push((Node){dis[i],i});
    memset(vis,0,sizeof(vis));
    while( pq.size() ) {
        const int pos = pq.top().pos; pq.pop();
        if( vis[pos] ) continue;
        vis[pos] = 1;
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] )
                pq.push((Node){dis[t[at]]=dis[pos]+l[at],t[at]});
    }
}

inline void getans() {
    for(int sta=1;sta<full;sta++) {
        for(int ss=sta;ss;ss=(ss-1)&sta)
            for(int pos=1;pos<=n;pos++)
                f[sta][pos] = std::min( f[sta][pos] , f[ss][pos] + f[sta^ss][pos] );
        dji(f[sta]);
    }
    for(int i=1;i<=n;i++) ans = std::min( ans , f[full-1][i] );
}

inline char nxtchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0;
    char ch;
    while( !isdigit(ch=nxtchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nxtchar()) );
    return ret;
}
inline lli getlli() {
    lli ret = 0;
    char ch;
    while( !isdigit(ch=nxtchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nxtchar()) );
    return ret;
}

int main() {
    static int k,m;
    static lli l;
    n = getint() , full = 1 << ( k = getint() ) , m = getint() , memset(f,0x3f,sizeof(f)) , ans = **f;
    for(int i=0;i<k;i++) f[1<<i][getint()] = 0;
    for(int i=1,a,b;i<=m;i++) a = getint() , b = getint() , l = getlli() , addedge(a,b,l) , addedge(b,a,l);
    getans() , printf("%lld\n",ans);
    return 0;
}