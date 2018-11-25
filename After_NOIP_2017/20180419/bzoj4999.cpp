#include<cstdio>
#include<algorithm>
#include<map>
const int maxn=1e5+1e2,maxr=3e5+1e2,maxe=1e7+1e2;

struct SegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void update(int &pos,int l,int r,const int &tar,const int &x) {
        if( !pos ) pos = ++cnt; sum[pos] += x;
        if( l == r ) return; const int mid = ( l + r ) >> 1;
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

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],id[maxn],iid;
int in[maxn],root[maxr],n;
std::map<int,int> mp;

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pre(t[at]) , siz[pos] += siz[t[at]] ,
        son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
    }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos , id[pos] = ++iid;
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
}
inline int chain(int x,int y,int rt) {
    int ret = 0;
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) std::swap(x,y);
        ret += sgt.query(rt,1,n,id[top[x]],id[x]) , x = fa[top[x]];
    }
    return ret += sgt.query(rt,1,n,std::min(id[x],id[y]),std::max(id[x],id[y]));
}

inline void check(int x) {
    static int cnt;
    if( mp.find(x) == mp.end() ) mp[x] = ++cnt;
}

int main() {
    static int m;
    static char o[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    pre(1) , dfs(1);
    for(int i=1;i<=n;i++) check(in[i]) , sgt.update(root[mp[in[i]]],1,n,id[i],1);
    for(int i=1,x,y,t;i<=m;i++) {
        scanf("%s%d%d",o,&x,&y);
        if( *o == 'Q' ) {
            scanf("%d",&t) , printf("%d\n",mp.find(t)!=mp.end()?chain(x,y,root[mp[t]]):0);
        } else if( *o == 'C' ) {
            sgt.update(root[mp[in[x]]],1,n,id[x],-1) , check(in[x]=y) , sgt.update(root[mp[in[x]]],1,n,id[x],1);
        }
    }
    return 0;
}

