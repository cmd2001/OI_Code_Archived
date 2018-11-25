#include<cstdio>
#include<algorithm>
const int maxn=2e5+1e2,maxe=5e6+1e2;

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int &pos,int pre,int l,int r,const int &tar) {
        pos = ++cnt , sum[pos] = sum[pre] + 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return sum[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
}pst;

int s[maxn],t[maxn],nxt[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],id[maxn];
int root[maxn],rt,n;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) {
        fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void dfs(int pos) {
    static int iid; id[pos] = ++iid , top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != son[pos] ) dfs(t[at]);
}
inline int chain(int x,int y,int root) {
    int ret = 0;
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) std::swap(x,y);
        ret += pst.query(root,1,n,id[top[x]],id[x]) , x = fa[top[x]];
    }
    ret += pst.query(root,1,n,std::min(id[x],id[y]),std::max(id[x],id[y]));
    return ret;
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) std::swap(x,y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int main() {
    static int m;
    scanf("%d",&n);
    for(int i=1,t;i<=n;i++) {
        scanf("%d",&t);
        if( t ) addedge(t,i);
        else rt = i;
    }
    pre(rt) , dfs(rt);
    scanf("%d",&m);
    for(int i=1,o,x,y,t;i<=m;i++) {
        scanf("%d%d",&o,&x) , root[i] = root[i-1];
        if( o == 2 ) pst.insert(root[i],root[i],1,n,id[x]);
        else scanf("%d%d",&y,&t) , printf("%d %d\n",dep[x]+dep[y]-(dep[lca(x,y)]<<1)+1,i<t?0:chain(x,y,root[i-t-1]));
    }
    return 0;
}
