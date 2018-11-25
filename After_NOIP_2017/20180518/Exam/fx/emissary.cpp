#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
//#define debug cerr
//using namespace std;
const int maxn=1e5+1e2,maxe=3.5e7+1e2;

int n,m;

struct SegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void update(int &pos,int l,int r,const int &tar,const int &x) {
        if( !pos ) { pos = ++cnt; } sum[pos] += x;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson[pos],l,mid,tar,x) : update(rson[pos],mid+1,r,tar,x);
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return sum[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
}sgt;

struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int x,const int &y,const int &val) {
        while( x <= n ) sgt.update(dat[x],1,n,y,val) , x += lowbit(x);
    }
    inline int query(int x,const int &ll,const int &rr) {
        int ret = 0;
        while(x) ret += sgt.query(dat[x],1,n,ll,rr) , x -= lowbit(x);
        return ret;
    }
    inline int query(int l,int r,const int &ll,const int &rr) {
        return query(r,ll,rr) - query(l-1,ll,rr);
    }
}bit;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int dep[maxn],dfn[maxn],rit[maxn],anc[maxn][22];

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    static int dd;
    dfn[pos] = ++dd , *anc[pos] = fa;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dep[t[at]] = dep[pos] + 1 , dfs(t[at],pos);
    rit[pos] = dd;
}
inline void pre() {
    for(int j=1;j<22;j++) for(int i=1;i<=n;i++) anc[i][j] = anc[anc[i][j-1]][j-1];
}
inline int lca(int x,int y) {
    if( dep[x] < dep[y] ) std::swap(x,y);
    for(int i=21;~i;i--) if( dep[x] - ( 1 << i ) >= dep[y] ) x = anc[x][i];
    if( x == y ) return x;
    for(int i=21;~i;i--) if( anc[x][i] != anc[y][i] ) x = anc[x][i] , y = anc[y][i];
    return *anc[x];
}
inline int nstson(int fa,int son) {
    for(int i=21;~i;i--) if( dep[son] - ( 1 << i ) > dep[fa] ) son = anc[son][i];
    return son;
}
inline int query(int x,int y) { // assert x != y .
    int lc = lca(x,y);
    if( lc != x && lc != y ) return bit.query(dfn[x],rit[x],dfn[y],rit[y]);
    else {
        if( lc != x ) std::swap(x,y);
        int ns = nstson(x,y);
        return bit.query(1,n,dfn[y],rit[y]) - bit.query(dfn[ns],rit[ns],dfn[y],rit[y]);
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    dfs(1,-1) , scanf("%d",&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , bit.update(dfn[a],dfn[b],1) , bit.update(dfn[b],dfn[a],1);
    scanf("%d",&m) , pre();
    for(int i=1,o,x,y;i<=m;i++) {
        scanf("%d%d%d",&o,&x,&y);
        if( o == 1 ) bit.update(dfn[x],dfn[y],1) , bit.update(dfn[y],dfn[x],1);
        else if( o == 2 ) bit.update(dfn[x],dfn[y],-1) , bit.update(dfn[y],dfn[x],-1);
        else if( o == 3 ) assert(x!=y) , printf("%d\n",query(x,y)); // if x == y , it will be an undefined input data .
    }
    return 0;
}

