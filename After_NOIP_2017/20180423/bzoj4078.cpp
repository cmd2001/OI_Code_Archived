#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=4e2+1e1,maxe=maxn*maxn;
const int inf=0x7fffffff;

int s[maxn],t[maxe<<2],nxt[maxe<<2],cnt;
int vis[maxn],ins[maxn],dfn[maxn],low[maxn],bel[maxn],stk[maxn],top,iid,dd;
int n,m,ans=inf;
int group[maxe],gcnt;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    vis[pos] = ins[stk[++top]=pos] = 1 , low[pos] = dfn[pos] = ++dd;
    for(int at=s[pos];at;at=nxt[at])
        if( !vis[t[at]] ) dfs(t[at]) , low[pos] = min( low[pos] , low[t[at]] );
        else if( ins[t[at]] ) low[pos] = min( low[pos] , dfn[t[at]] );
    if( low[pos] == dfn[pos] ) {
        ++iid;
        do {
            const int x = stk[top--]; ins[x] = 0 , bel[x] = iid;
        } while( ins[pos] );
    }
}

inline int cov(int x,int tpe) {
    return x * 2 - 1 + tpe;
}
inline bool core_judge() {
    for(int i=1;i<n<<1;i++) if( !vis[i] ) dfs(i);
    for(int i=1;i<=n;i++) if( bel[cov(i,0)] == bel[cov(i,1)] ) return 0;
    return 1;
}

struct Node {
    int x,y,val;
    friend bool operator < (const Node &a,const Node &b) {
        return a.val != b.val ? a.val < b.val : a.x != b.x ? a.x < b.x : a.y < b.y;
    }
}ns[maxe];

inline bool judge(int lim0,int lim1) { // assert lim0 <= lim1 .
    memset(s,0,sizeof(s)) , memset(vis,0,sizeof(vis)) , cnt = top = iid = dd = 0;
    for(int i=lim1+1;i<=m;i++) {
        addedge(cov(ns[i].x,0),cov(ns[i].y,1)) , addedge(cov(ns[i].y,0),cov(ns[i].x,1)) , 
        addedge(cov(ns[i].x,1),cov(ns[i].y,0)) , addedge(cov(ns[i].y,1),cov(ns[i].x,0)) ;
    } for(int i=lim0+1;i<=lim1;i++) addedge(cov(ns[i].x,1),cov(ns[i].y,0)) , addedge(cov(ns[i].y,1),cov(ns[i].x,0));
    return core_judge();
}

inline int bin(int lim0) {
    int l = 0 , r = lim0, mid;
    if( judge(0,lim0) ) return 0;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid,lim0) ) r = mid;
        else l = mid; 
    }
    return r;
}

struct UnionFindSet {
    int fa[maxn],rel[maxn];
    inline int findfa(int x) {
        if( fa[x] == x ) return x;
        const int f = fa[x];
        fa[x] = findfa(fa[x]) , rel[x] ^= rel[f];
        return fa[x];
    }
    inline bool same(int x,int y) {
        return findfa(x) == findfa(y);
    }
    inline void merge(int x,int y) {
        int fx = findfa(x) , fy = findfa(y);
        fa[fx] = fy , rel[fx] = rel[x] ^ rel[y] ^ 1;
    }
    inline bool fail(int x,int y) {
        findfa(x) , findfa(y);
        return ! ( rel[x] ^ rel[y] );
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

int main() {
    scanf("%d",&n) , ufs.init();
    if( n <= 2 ) return puts("0"),0;
    for(int i=1;i<=n;i++) for(int j=i+1,v;j<=n;j++) scanf("%d",&v) , ns[++m] = (Node){i,j,v};
    sort(ns+1,ns+1+m);
    for(int i=m;i;i--) {
        if( !ufs.same(ns[i].x,ns[i].y) ) group[++gcnt] = i , ufs.merge(ns[i].x,ns[i].y);
        else group[gcnt] = i;
        if( ufs.fail(ns[i].x,ns[i].y) ) break;
    }
    for(int i=1;i<=gcnt;i++) if( group[i] ) ans = min( ans , ns[group[i]].val + ns[bin(group[i])].val );
    printf("%d\n",ans);
    return 0;
}

