#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

int from[maxn<<1],to[maxn<<1],ing[maxn<<1],cutnum[maxn<<1];
lli disst[maxn],dised[maxn],len[maxn<<1];
int bel[maxn],cid[maxn],cnt;
int n,egs,m,s,t;

struct Graph {
    int s[maxn],t[maxn<<2],nxt[maxn<<2];
    lli l[maxn<<2];
    inline void addedge(int from,int to,int len) {
        static int cnt = 0;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
}graph;

namespace ShorestPath {
    int *s,*t,*nxt;
    int st,ed;
    lli *l,*dis;
    
    struct Node {
        lli dd;
        int pos;
        friend bool operator < (const Node &a,const Node &b) {
            return a.dd != b.dd ? a.dd < b.dd : a.pos < b.pos;
        }
    };
    set<Node> heap;
    inline void reset() {
        for(int i=0;i<=n;i++)
            dis[i] = inf;
        heap.clear();
        dis[st] = 0;
    }
    inline void dji() {
        reset();
        for(int i=1;i<=n;i++)
            heap.insert((Node){dis[i],i});
        for(int i=1;i<=n;i++) {
            const int pos = heap.begin()->pos;
            heap.erase(heap.begin());
            for(int at=s[pos];at;at=nxt[at])
                if( dis[t[at]] > dis[pos] + l[at] ) {
                    heap.erase((Node){dis[t[at]],t[at]});
                    dis[t[at]] = dis[pos] + l[at];
                    heap.insert((Node){dis[t[at]],t[at]});
                }
        }
    }
    inline void calc(Graph &g,lli* ddis,int sst,int eed) {
        s = g.s , t = g.t , nxt = g.nxt , l = g.l;
        dis = ddis , st = sst , ed = eed;
        dji();
    }
}

namespace Tarjan {
    int s[maxn],t[maxn<<2],nxt[maxn<<2],eid[maxn<<2];
    int dfn[maxn],low[maxn]; // cid :: brigde's cid of lower block
    int vis[maxn],ins[maxn],stk[maxn],top;
    int dd;
    
    inline void addedge(int from,int to,int edg) {
        static int cnt = 0;
        t[++cnt] = to , eid[cnt] = edg,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    
    inline void dfs(int pos,int fa) {
        vis[pos] = 1;
        low[pos] = dfn[pos] = ++dd;
        stk[++top] = pos , ins[pos] = 1;
        for(int at=s[pos];at;at=nxt[at])
            if( !vis[t[at]] ) {
                dfs(t[at],pos);
                low[pos] = min( low[pos] , low[t[at]] );
                if( low[t[at]] > low[pos] ) {
                    if( ins[t[at]] ) debug<<"ERROR :: STILL IN STACK"<<endl;
                    cid[bel[t[at]]-1] = eid[at];
                }
            }
            else if( t[at] != fa )
                low[pos] = min( low[pos] , dfn[t[at]] );
        if( dfn[pos] == low[pos] ) {
            ++cnt;
            do {
                bel[stk[top]] = cnt;
                ins[stk[top]] = 0;
                --top;
            }while( ins[pos] );
        }
    }
    
}
struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
    lli mi[maxn<<3];
    
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr , mi[pos] = inf;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void update(int pos,int ll,int rr,lli x) {
        if( r[pos] < ll || rr < l[pos] ) return;
        if( ll <= l[pos] && r[pos] <= rr ) {
            mi[pos] = min( mi[pos] , x );
            return;
        }
        update(lson[pos],ll,rr,x);
        update(rson[pos],ll,rr,x);
        mi[pos] = min( mi[lson[pos]] , mi[rson[pos]] );
    }
    inline lli query(int pos,int tar) {
        if( tar < l[pos] || r[pos] < tar ) return inf;
        if( l[pos] <= tar && tar <= r[pos] ) return mi[pos];
        return min( query(lson[pos],tar) , query(rson[pos],tar) );
    }
    inline void init(int ss) {
        build(cnt=1,1,ss);
    }
}segt;

int main() {
    static int q;
    scanf("%d%d",&n,&m);
    for(int i=1,x,y,l;i<=n;i++) {
        scanf("%d%d%d",&x,&y,&l);
        graph.addedge(x,y,l);
        from[++egs] = x , to[egs] = y , len[egs] = l;
    }
    scanf("%d%d",&s,&t);
    ShorestPath::calc(graph,disst,s,t);
    ShorestPath::calc(graph,dised,t,s);
    
    for(int i=1;i<=egs;i++)
        if( disst[from[i]] + len[i] + dised[to[i]] == disst[t] ) {
            ing[i] = 1;
            Tarjan::addedge(from[i],to[i],i);
        }
    Tarjan::dfs(s,-1);
    for(int i=1;i<=cnt;i++)
        cutnum[cid[i]] = i;
    segt.init(cnt);
    
    for(int i=1;i<=egs;i++)
        if( bel[from[i]] != bel[to[i]] ) {
            segt.update(1,min(bel[from[i]],bel[to[i]]),max(bel[from[i]],bel[to[i]])-1,disst[from[i]]+dised[to[i]]+len[i]);
        }
    
    scanf("%d",&q);
    for(int i=1,id;i<=q;i++) {
        scanf("%d",&id);
        if( !cutnum[id] ) {
            printf("%lld\n",disst[t]);
        } else {
            lli ans = segt.query(1,cutnum[id]);
            if( ans != inf ) printf("%lld\n",ans);
            else puts("Infinity");
        }
    }
    
    return 0;
}
