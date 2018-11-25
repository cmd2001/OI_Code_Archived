#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=3e4+1e2;
const int inf=0x3f3f3f3f;

struct Node {
    int crs[2][2],fm[2][2]; // crs :: [up/down][up/down] , fm :: [left/right][up/down]
    Node() {
        memset(crs,0,sizeof(crs)) , memset(fm,0,sizeof(fm));
    }
    inline void res() {
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                crs[i][j] = fm[i][j] = -inf;
    }
    inline void fill(int up,int down) {
        res();
        crs[0][0] = fm[0][0] = fm[1][0] = up , crs[1][1] = fm[0][1] = fm[1][1] = down;
        if( up && down ) crs[0][1] = crs[1][0] = fm[0][0] = fm[0][1] = fm[1][0] = fm[1][1] = 2;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++) {
                if( !crs[i][j] ) crs[i][j] = -inf;
                if( !fm[i][j] ) fm[i][j] = -inf;
            }
    }
    friend Node operator + (const Node &l,const Node &r) {
        Node ret;
        ret.res();
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++) {
                for(int k=0;k<2;k++)
                    ret.crs[i][j] = max( ret.crs[i][j] , l.crs[i][k] + r.crs[k][j] );
                if( ret.crs[i][j] < 0 ) ret.crs[i][j] = -inf;
            }
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++) {
                ret.fm[i][j] = ( !i ) ? l.fm[i][j] : r.fm[i][j];
                for(int k=0;k<2;k++) {
                    if( !i ) ret.fm[i][j] = max( ret.fm[i][j] , l.crs[j][k] + r.fm[i][k] );
                    else ret.fm[i][j] = max( ret.fm[i][j] , l.fm[i][k] + r.crs[k][j] );
                }
                if( ret.fm[i][j] < 0 ) ret.fm[i][j] = -inf;
            }
        return ret;
    }
    inline Node reverse() {
        Node ret = *this;
        swap( ret.crs[0][1] , ret.crs[1][0] );
        swap( ret.fm[0][0] , ret.fm[1][0] );
        swap( ret.fm[0][1] , ret.fm[1][1] );
        return ret;
    }
}ns[maxn<<3];

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn],num[maxn],cov[maxn],fd[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
char in[maxn][3];

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        ns[pos].fill(in[fd[ll]][0],in[fd[ll]][1]);
        return;
    }
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline void update(int pos,int tar) {
    if( tar < l[pos] || r[pos] < tar ) return;
    if( l[pos] == r[pos] && l[pos] == tar ) {
        ns[pos].fill(in[fd[tar]][0],in[fd[tar]][1]);
        return;
    }
    update(lson[pos],tar);
    update(rson[pos],tar);
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline Node query(int pos,const int &ll,const int &rr) {
    if( ll <= l[pos] && r[pos] <= rr ) {
        return ns[pos];
    }
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid ) return query(lson[pos],ll,rr);
    if( ll > mid ) return query(rson[pos],ll,rr);
    return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1;
            pre(t[at]);
            siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    num[pos] = pos == son[fa[pos]] ? num[fa[pos]] + 1 : 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] )
            dfs(t[at]);
    if( !son[pos] ) {
        cov[top[pos]] = ++cnt;
        for(int pp=pos;pp;pp=fa[pp]) {
            fd[num[pp]] = pp;
            if( pp == top[pp] ) break;
        }
        build(cov[top[pos]],num[top[pos]],num[pos]);
    }
}
inline int lca(int a,int b) {
    while( top[a] != top[b] )
        dep[top[a]] > dep[top[b]] ? a = fa[top[a]] : b = fa[top[b]];
    return dep[a] < dep[b] ? a : b;
}
inline Node querychain(int a,int l,int flag) {// flag = 1 means include b . 
    if( top[a] == top[l] )
        return query(cov[top[a]],num[l]+1-flag,num[a]);
    Node ret = query(cov[top[a]],num[top[a]],num[a]);
    a = fa[top[a]];
    while( top[a] != top[l] ) {
        ret = query(cov[top[a]],num[top[a]],num[a]) + ret ,
        a = fa[top[a]];
    }
    if( !flag && a == l ) return ret;
    ret = query(cov[top[a]],num[l]+1-flag,num[a]) + ret;
    return ret;
}
inline Node getans(int a,int b) {
    int l = lca(a,b);
    if( a == l ) {
        return querychain(b,l,1);
    } else if( b == l ) {
        return querychain(a,l,1).reverse();
    } else {
        return querychain(a,l,0).reverse() + querychain(b,l,1) ;
    }
}

int main() {
    //freopen("dat.txt","r",stdin);
    //freopen("my.txt","w",stdout);
    static int n,m;
    static char com[10];
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b) , addedge(b,a);
    }
    for(int i=1;i<=n;i++) {
        scanf("%s",in[i]);
        for(int j=0;j<2;j++) in[i][j] = ( in[i][j] == '.' );
    }
    
    pre(1);
    dfs(1);
    
    for(int i=1,u,v;i<=m;i++) {
        scanf("%s%d",com,&u);
        if( *com == 'Q' ) {
            scanf("%d",&v);
            if( !in[u][0] && !in[u][1] ) {
                puts("0");
                continue;
            }
            Node ans = getans(u,v);
            printf("%d\n",max( ans.fm[0][0] , ans.fm[0][1] ) );
        } else {
            scanf("%s",in[u]);
            for(int j=0;j<2;j++)
                in[u][j] = ( in[u][j] == '.' );
            fd[num[u]] = u;
            update(cov[top[u]],num[u]);
        }
    }
    return 0;
}
