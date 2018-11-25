#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cctype>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=4e5+1e2,maxe=1e6+1e2,maxm=1e5+1e2;
const lli inf = 0x3f3f3f3f3f3f3f3fll;

int cnt;

struct Edge {
    int val,id;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.val < b.val;
    }
};
vector<Edge> es[maxm];
vector<int> ts;

struct Node {
    lli dis;
    int pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis > b.dis;
    }
};
priority_queue<Node> pq;
int s[maxn],t[maxe],l[maxn],nxt[maxe];
lli dis[maxn] , ans = inf;

inline void addedge(int from,int to,int len) {
    static int cnt;
    debug<<"from = "<<from<<"to = "<<to<<endl;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dji() {
    for(int i=1;i<=cnt;i++) if( dis[i] != inf ) pq.push((Node){dis[i],i});
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
    n = getint() , m = getint() , memset(dis,0x3f,sizeof(dis));
    for(int i=1,a,b,l;i<=m;i++) {
        a = getint() , b = getint() , l = getint();
        if( a > b ) swap(a,b);
        es[a].push_back((Edge){l,++cnt}) , es[b].push_back((Edge){l,++cnt});
        addedge(cnt-1,cnt,0) , addedge(cnt,cnt-1,0);
        if( a == 1 ) dis[cnt-1] = l;
        if( b == n ) ts.push_back(cnt-1);
    }
    for(int i=1;i<=n;i++) if( es[i].size() ) {
        sort(es[i].begin(),es[i].end());
        for(unsigned j=0;j<es[i].size();j++) {
            if( j ) addedge(es[i][j].id,es[i][j-1].id,0);
            if( j != es[i].size() - 1 ) addedge(es[i][j].id,es[i][j+1].id,es[i][j+1].val-es[i][j].val);
        }
    }
    dji();
    for(unsigned i=0;i<ts.size();i++) ans = min( ans , dis[ts[i]] );
    printf("%lld\n",ans);
    return 0;
}

