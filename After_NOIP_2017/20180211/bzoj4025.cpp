#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1e5+1e2;

struct Node {int x,y;};
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
vector<Node> ns[maxn<<3];

int fa[maxn],siz[maxn],rel[maxn];
int stk[maxn<<1],top;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
}
inline void update(int pos,int ll,int rr,Node e) {
    if( rr < l[pos] || r[pos] < ll ) return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        ns[pos].push_back(e);
        return;
    }
    update(lson[pos],ll,rr,e) , update(rson[pos],ll,rr,e);
}

inline int findfa(int x) {
    return fa[x] == x ? x : findfa(fa[x]);
}
inline int getrel(int x) {
    return fa[x] == x ? 0 : rel[x] ^ getrel(fa[x]);
}
inline void merge(int x,int y) {
    int fx = findfa(x) , rx = getrel(x) ;
    int fy = findfa(y) , ry = getrel(y) ;
    if( siz[fx] < siz[fy] ) swap( fx , fy ) , swap( rx , ry );
    stk[++top] = fy;
    fa[fy] = fx , siz[fx] += siz[fy] , rel[fy] = rx ^ ry ^ 1;
}
inline void reset(int tar) {
    while( top > tar ) {
        const int pos = stk[top--];
        const int f = findfa(pos);
        siz[f] -= siz[pos] , fa[pos] = pos , rel[pos] = 0;
    }
}
inline void dfs(int pos) {
    bool flag = 0;
    int mem = top;
    for(unsigned i=0;i<ns[pos].size()&&!flag;i++) {
        if( findfa(ns[pos][i].x) == findfa(ns[pos][i].y) ) flag = getrel(ns[pos][i].x) ^ getrel(ns[pos][i].y) ^ 1;
        else merge(ns[pos][i].x,ns[pos][i].y);
    }
    if( flag ) {
        for(int i=l[pos];i<=r[pos];i++) puts("No");
        reset(mem);
        return;
    } else if( l[pos] == r[pos] ) {
        puts("Yes");
        reset(mem);
        return;
    }
    dfs(lson[pos]) , dfs(rson[pos]);
    reset(mem);
}

int main() {
    static int n,m,t;
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;i++) fa[i] = i , siz[i] = 1 ;
    build(cnt=1,1,t);
    for(int i=1,u,v,st,ed;i<=m;i++) {
        scanf("%d%d%d%d",&u,&v,&st,&ed);
        if( st == ed ) continue;
        update(1,st+1,ed,(Node){u,v});
    }
    dfs(1);
    return 0;
}

