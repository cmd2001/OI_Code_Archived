#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=2e4+1e2;

struct Node {
    lli dat[62];
    inline void insert(lli x) {
        for(int i=60;~i;i--)
            if( ( x >> i ) & 1 ) {
                if( !dat[i] ) {
                    dat[i] = x;
                    break;
                } else x ^= dat[i];
            }
    }
    inline void merge(const Node &r) {
        for(int i=60;~i;i--)
            if( r.dat[i] ) {
                insert(r.dat[i]);
            }
    }
    inline lli query() {
        lli ret = 0;
        for(int i=60;~i;i--)
            ret = max( ret , ret ^ dat[i] );
        return ret;
    }
    friend Node operator + (const Node &a,const Node &b) {
        Node ret = a;
        ret.merge(b);
        return ret;
    }
    inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}ns[maxn<<3],ans;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
int dep[maxn],siz[maxn],son[maxn],fa[maxn],top[maxn],id[maxn],cov[maxn];
lli in[maxn],chain[maxn];

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        ns[pos].insert(chain[ll]);
        return;
    }
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline void query(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        ans.merge(ns[pos]);
        return;
    }
    query(lson[pos],ll,rr);
    query(rson[pos],ll,rr);
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 ;
            pre(t[at]);
            siz[pos] += siz[t[at]];
            son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    id[pos] = pos == son[fa[pos]] ? id[fa[pos]] + 1 : 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] )
            dfs(t[at]);
    if( !son[pos] ) {
        for(int i=pos;;i=fa[i]) {
            chain[id[i]] = in[i];
            if( i == top[i] ) break;
        }
        build(cov[top[pos]]=++cnt,id[top[pos]],id[pos]);
    }
}
inline void lca(int x,int y) {
    ans.reset();
    while( top[x] != top[y] ) {
        if( dep[top[x]] > dep[top[y]] ) {
            query(cov[top[x]],id[top[x]],id[x]);
            x = fa[top[x]];
        } else {
            query(cov[top[y]],id[top[y]],id[y]);
            y = fa[top[y]];
        }
    }
    if( id[x] > id[y] ) swap(x,y);
    query(cov[top[x]],id[x],id[y]);
}

int main() {
    static int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b) , addedge(b,a);
    }
    pre(1);
    dfs(1);
    for(int i=1,x,y;i<=q;i++) {
        scanf("%d%d",&x,&y);
        lca(x,y);
        printf("%lld\n",ans.query());
    }
    return 0;
}
