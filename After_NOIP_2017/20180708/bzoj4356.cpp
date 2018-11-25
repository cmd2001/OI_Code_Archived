#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1.6e5+1e3,maxt=4e2+1e1;

int n,m;

int sel[maxt][maxt],a[maxt][maxt],b[maxt][maxt]; // a links (x,y) and (x+1,y) , b links (x,y) and (x,y+1)
bool on[maxn],ona[maxt][maxt],onb[maxt][maxt];

struct Node {
    lli dis; int pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis > b.dis;
    }
};

namespace OriGraph {
    int s[maxn],t[maxn<<3],nxt[maxn<<3],l[maxn<<3];
    int sou[maxn],soue[maxn]; lli dis[maxn]; bool vis[maxn];
    inline void coredge(int from,int to,int len) {
        static int cnt = 1;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void dji(int st) {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        priority_queue<Node> q; q.push((Node){dis[st],st});
        while( q.size() ) {
            const int pos = q.top().pos; q.pop();
            if( vis[pos] ) continue;
            for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] ) {
                sou[t[at]] = pos , soue[t[at]] = at , q.push((Node){dis[t[at]]=dis[pos]+l[at],t[at]});
            }
        }
    }
    inline int cov(int x,int y) {
        return m * --x + y;
    }
    inline void markall() {
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
            if( i != n ) addedge(cov(i,j),cov(i+1,j),a[i][j]);
            if( j != m ) addedge(cov(i,j),cov(i,j+1),b[i][j]);
        }
        dji(cov(1,1));
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( sel[i][j] ) {
            for(int t=cov(i,j);t&&!on[t];t=sou[t]) on[t] = 1;
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( on[cov(i,j)] ) {
            if( i != n && on[cov(i+1,j)] && ( t[soue[cov(i+1,j)]^1] == cov(i,j) || t[soue[cov(i,j)]^1] == cov(i+1,j) ) ) ona[i][j] = 1;
            if( j != m && on[cov(i,j+1)] && ( t[soue[cov(i,j+1)]^1] == cov(i,j) || t[soue[cov(i,j)]^1] == cov(i,j+1) ) ) onb[i][j] = 1;
        }
        /*for(int i=1;i<=n;i++) {
            for(int j=1;j<=m;j++) debug<<dis[cov(i,j)]<<" "; debug<<endl;
        }*/
    }
}

namespace Graph {
    int s[maxn<<2],t[maxn<<5],nxt[maxn<<5],l[maxn<<5];
    lli dis[maxn<<2]; bool vis[maxn<<2];
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline lli dji(int st,int ed) {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        priority_queue<Node> q; q.push((Node){dis[st],st});
        while( q.size() ) {
            const int pos = q.top().pos; q.pop();
            if( vis[pos] ) continue;
            for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] )
                q.push((Node){dis[t[at]]=dis[pos]+l[at],t[at]});
        }
        return dis[ed];
    }
    inline int cov(int x,int y,int tpe) { // tpe from 0 to 3 .
        return ( m * -- x + y ) * 4 - 3 + tpe;
    }
    inline void build() {
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
            if( !ona[i-1][j] && !sel[i-1][j-1] && !sel[i-1][j] ) addedge(cov(i,j,0),cov(i,j,1),0);
            if( !ona[i][j] && !sel[i][j-1] && !sel[i][j] )  addedge(cov(i,j,2),cov(i,j,3),0);
            if( !onb[i][j-1] && !sel[i-1][j-1] && !sel[i][j-1] ) addedge(cov(i,j,0),cov(i,j,3),0);
            if( !onb[i][j] && !sel[i-1][j] && !sel[i][j] ) addedge(cov(i,j,1),cov(i,j,2),0);
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
            if( i != n ) {
                addedge(cov(i,j,3),cov(i+1,j,0),a[i][j]);
                addedge(cov(i,j,2),cov(i+1,j,1),a[i][j]);
            }
            if( j != m ) {
                addedge(cov(i,j,1),cov(i,j+1,0),b[i][j]);
                addedge(cov(i,j,2),cov(i,j+1,3),b[i][j]);
            }
        }
    }
}

int main() {
    scanf("%d%d",&n,&m) , ++n , ++m , **sel = 1;
    for(int i=1;i<n;i++) for(int j=1;j<m;j++) scanf("%d",sel[i]+j);
    for(int i=1;i<n;i++) for(int j=1;j<=m;j++) scanf("%d",a[i]+j);
    for(int i=1;i<=n;i++) for(int j=1;j<m;j++) scanf("%d",b[i]+j);
    OriGraph::markall() , Graph::build() , printf("%lld\n",Graph::dji(Graph::cov(1,1,1),Graph::cov(1,1,3)));
    return 0;
}
