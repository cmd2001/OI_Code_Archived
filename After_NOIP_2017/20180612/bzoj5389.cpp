#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
#include<cctype>
typedef long long int lli;
const int maxn=5e5+1e2;

int n;

struct Node {
    lli w;
    int siz,id;
    friend bool operator < (const Node &a,const Node &b) {
        return  a.w * b.siz !=  b.w * a.siz ? a.w * b.siz < b.w * a.siz : a.id < b.id;
    }
};
std::set<Node> st;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void link(int from,int to) {
        fa[findfa(from)] = to;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

int in[maxn],siz[maxn];
lli w[maxn],ans;
int s[maxn],t[maxn],nxt[maxn],deg[maxn];

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to];
}
inline bool topo() { // return 1 if failed .
    std::queue<int> q;
    for(int i=0;i<=n;i++) if( !deg[i] ) q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at]) if( !--deg[t[at]] ) q.push(t[at]);
    }
    for(int i=1;i<=n;i++) if( deg[i] ) return 1;
    return 0;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , ufs.init();
    for(int i=1;i<=n;i++) addedge(in[i]=getint(),i);
    for(int i=1;i<=n;i++) ans += ( w[i] = getint() );
    if( topo() ) return puts("-1") , 0;
    for(int i=1;i<=n;i++) st.insert((Node){w[i],siz[i]=1,i});
    while( st.size() ) {
        const Node pos = *st.begin(); st.erase(st.begin());
        const int x = pos.id , y = ufs.findfa(in[x]);
        if( y ) st.erase((Node){w[y],siz[y],y});
        ans += w[x] * siz[y] , w[y] += w[x] , siz[y] += siz[x] , ufs.link(x,y);
        if( y ) st.insert((Node){w[y],siz[y],y});
    }
    printf("%lld\n",ans);
}
