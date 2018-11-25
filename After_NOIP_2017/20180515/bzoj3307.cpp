#include<cstdio>
#include<algorithm>
const int maxn=1e5+1e2,maxe=7e6+1e2;

struct SemgnetTree {
    int lson[maxe],rson[maxe],mp[maxe],mv[maxe],cnt;
    inline void insert(int &pos,int l,int r,const int &tar,const int &x) {
        if( !pos ) pos = ++cnt;
        if( l == r ) {
            mv[pos] += x , mp[pos] = mv[pos] ? l : 0;
            return;
        } const int mid = ( l + r ) >> 1;
        tar <= mid ? insert(lson[pos],l,mid,tar,x) : insert(rson[pos],mid+1,r,tar,x);
        if( mv[lson[pos]] >= mv[rson[pos]] ) mp[pos] = mp[lson[pos]] , mv[pos] = mv[lson[pos]];
        else mp[pos] = mp[rson[pos]] , mv[pos] = mv[rson[pos]];
    }
    inline int merge(int x,int y,int l,int r) {
        if( !x || !y ) return x | y;
        if( l == r ) {
            mv[x] += mv[y] , mp[x] = mv[x] ? l : 0;
            return x;
        }
        const int mid = ( l + r ) >> 1;
        lson[x] = merge(lson[x],lson[y],l,mid) , rson[x] = merge(rson[x],rson[y],mid+1,r);
        if( mv[lson[x]] >= mv[rson[x]] ) mp[x] = mp[lson[x]] , mv[x] = mv[lson[x]];
        else mp[x] = mp[rson[x]] , mv[x] = mv[rson[x]];
        return x;
    }
}sgt;

int x[maxn],y[maxn],z[maxn],srt[maxn],len;
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn],rot[maxn],ans[maxn];

inline void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline void dfs1(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , dfs1(t[at]) , siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
}
inline void dfs2(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs2(t[at]);
}
inline void dfs3(int pos) {
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs3(t[at]);
    ans[pos] = sgt.mp[rot[pos]];
    if( fa[pos] ) rot[fa[pos]] = sgt.merge(rot[fa[pos]],rot[pos],1,len);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , doubledge(a,b);
    dfs1(1) , dfs2(1);
    for(int i=1;i<=m;i++) scanf("%d%d%d",x+i,y+i,z+i) , srt[i] = z[i];
    std::sort(srt+1,srt+1+m) , len = std::unique(srt+1,srt+1+m) - srt - 1;
    for(int i=1;i<=m;i++) z[i] = std::lower_bound(srt+1,srt+1+len,z[i]) - srt;
    for(int i=1,a,b,z,l;i<=m;i++) {
        a = x[i] , b = y[i] , z = ::z[i] , l = lca(a,b) , sgt.insert(rot[a],1,len,z,1) , sgt.insert(rot[b],1,len,z,1) , sgt.insert(rot[l],1,len,z,-1);
        if( fa[l] ) sgt.insert(rot[fa[l]],1,len,z,-1);
    }
    dfs3(1);
    for(int i=1;i<=n;i++) printf("%d\n",srt[ans[i]]);
    return 0;
}
