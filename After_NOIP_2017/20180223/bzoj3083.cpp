#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
    lli lazy[maxn<<3],dat[maxn<<3];
    
    SegmentTree() {
        memset(lazy,-1,sizeof(lazy)) , memset(dat,0x3f,sizeof(dat));
    }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void fill(int pos,lli val) {
        if( !pos ) return;
        lazy[pos] = dat[pos] = val;
    }
    inline void push(int pos) {
        if( ~lazy[pos] ) {
            fill(lson[pos],lazy[pos]) , fill(rson[pos],lazy[pos]) ,
            lazy[pos] = -1;
        }
    }
    inline void update(int pos,int ll,int rr,lli v) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return fill(pos,v);
        push(pos);
        update(lson[pos],ll,rr,v) , update(rson[pos],ll,rr,v);
        dat[pos] = min( dat[lson[pos]] , dat[rson[pos]] );
    }
    inline lli query(int pos,int ll,int rr) {
        if( rr < l[pos] || r[pos] < ll ) return inf;
        if( ll <= l[pos] && r[pos] <= rr ) return dat[pos];
        push(pos);
        return min(query(lson[pos],ll,rr),query(rson[pos],ll,rr));
    }
}st;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn],id[maxn],rit[maxn],iid;
lli in[maxn];
int n,m,root;

inline void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to) {
    coredge(from,to) , coredge(to,from);
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos;
            pre(t[at]) , siz[pos] += siz[t[at]];
            son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    id[pos] = ++iid , st.update(1,id[pos],id[pos],in[pos]);
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] !=fa[pos] && t[at] != son[pos] )
            dfs(t[at]);
    rit[pos] = iid;
}
inline void chain(int x,int y,int v) {
    while( top[x] != top[y] ) {
        if( dep[top[x]] > dep[top[y]] ) {
            st.update(1,id[top[x]],id[x],v);
            x = fa[top[x]];
        } else {
            st.update(1,id[top[y]],id[y],v);
            y = fa[top[y]];
        }
    }
    if( id[x] > id[y] ) swap(x,y);
    st.update(1,id[x],id[y],v);
}
inline int gid(int root,int pos) {
    int lst = 0;
    while( top[root] != top[pos] ) lst = root , root = fa[root];
    if( root == pos ) return lst;
    return son[pos];
}
inline lli query(int pos) {
    if( root == pos ) return st.query(1,1,n);
    if( id[root] < id[pos] || rit[pos] < id[root] ) return st.query(1,id[pos],rit[pos]);
    int t = gid(root,pos);
    lli ret = inf;
    if( id[t] != 1 ) ret = min( ret , st.query(1,1,id[t]-1) );
    if( rit[t] != inf ) ret = min( ret , st.query(1,rit[t]+1,n) );
    return ret;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
inline lli getlli() {
    lli ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    n = getint() , m = getint();
    for(int i=1,a,b;i<n;i++) {
        a = getint() , b = getint();
        doubledge(a,b);
    }
    for(int i=1;i<=n;i++) in[i] = getlli();
    root = getint();
    st.build(st.cnt=1,1,n);
    pre(1) , dfs(1);
    for(int i=1,o,u,v;i<=m;i++) {
        o = getint();
        if( o == 1 ) root = getint();
        else if( o == 2 ) {
            u = getint() , v = getint();
            chain(u,v,getlli());
        } else if( o == 3 ) {
            u = getint();
            printf("%lld\n",query(u));
        }
    }
    return 0;
}
