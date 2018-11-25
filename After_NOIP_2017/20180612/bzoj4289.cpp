#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cctype>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=8e5+1e2,maxe=1.6e6+1e2,maxt=1e5+1e2;
const lli inf = 0x3f3f3f3f3f3f3f3fll;

int st,ed;

struct Edge {
    int val,idi,ido;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.val < b.val;
    }
};
vector<Edge> es[maxt];

struct Node {
    lli dis;
    int pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis > b.dis;
    }
};

int s[maxn],t[maxe],l[maxe],nxt[maxe];
lli dis[maxn];

inline void addedge(int from,int to,int len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dji() {
    priority_queue<Node> pq;
    dis[st] = 0 , pq.push((Node){dis[st],st});
    while( pq.size() ) {
        const Node cur = pq.top(); pq.pop();
        if( dis[cur.pos] != cur.dis ) continue;
        const int pos = cur.pos;
        for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] ) pq.push((Node){dis[t[at]]=dis[pos]+l[at],t[at]});
    }
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int n,m;
    n = getint() , m = getint();
    st = m * 4 + 1 , ed = m * 4 + 2 , memset(dis,0x3f,sizeof(dis));
    for(int i=1,a,b,l;i<=m;i++) {
        a = getint() , b = getint() , l = getint();
        if( a > b ) swap(a,b);
        es[a].push_back((Edge){l,4*i-3,4*i-2}) , es[b].push_back((Edge){l,4*i-1,4*i});
        addedge(4*i-3,4*i-2,l) , addedge(4*i-1,4*i,l);
        addedge(4*i-2,4*i-1,0) , addedge(4*i,4*i-3,0);
        if( a == 1 ) addedge(st,4*i-3,l);
        if( b == n ) addedge(4*i-2,ed,0);
    }
    for(int i=1;i<=n;i++) if( es[i].size() ) {
        sort(es[i].begin(),es[i].end());
        for(unsigned j=0;j<es[i].size();j++) {
            if( j ) addedge(es[i][j].idi,es[i][j-1].idi,0);
            if( j != es[i].size() - 1 ) addedge(es[i][j].idi,es[i][j+1].idi,es[i][j+1].val-es[i][j].val);
        }
    }
    dji();
    printf("%lld\n",dis[ed]);
    return 0;
}
