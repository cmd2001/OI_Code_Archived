#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cstdlib>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
lli dis[maxn],l[maxn<<1];
int dep[maxn],fa[maxn],siz[maxn],top[maxn],son[maxn],id[maxn],rec[maxn],usl[maxn],usr[maxn];
set<int> cs[maxn];

struct SegmentTree {
    struct Equation { // k * dep + b == tme .
        lli k,b;
        inline lli calc(const lli &x) const {
            return k * x + b;
        }
    }es[maxn<<2];
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],used[maxn<<2],dat[maxn<<2],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void fill(int pos,const Equation &e) {
        used[pos] = 1 , es[pos] = e;
    }
    inline void reset(int pos) {
        used[pos] = 0;
    }
    inline void update(int pos,int ll,int rr,const Equation &e) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return fill(pos,e);
        update(lson[pos],ll,rr,e) , update(rson[pos],ll,rr,e);
    }
    inline void reset(int pos,int ll,int rr) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return reset(pos);
        reset(lson[pos],ll,rr) , reset(rson[pos],ll,rr);
    }
    inline Equation query(int pos,int tar) {
        if( used[pos] ) return es[pos];
        // may cause infinity rec-call .
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) return query(lson[pos],tar);
        else return query(rson[pos],tar);
    }
    inline void update_mx(int pos,const int &tar,const int &x) {
        if( l[pos] == r[pos] ) return void(dat[pos]=x);
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) update_mx(lson[pos],tar,x);
        else update_mx(rson[pos],tar,x);
        dat[pos] = max( dat[lson[pos]] , dat[rson[pos]] );
    }
    inline int query_mx(int pos,int ll,int rr) {
        if( rr < l[pos] || r[pos] < ll ) return -1;
        if( ll <= l[pos] && r[pos] <= rr ) return dat[pos];
        return max( query_mx(lson[pos],ll,rr) , query_mx(rson[pos],ll,rr) );
    }
}sgt;
typedef SegmentTree::Equation Equation;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , dis[t[at]] = dis[pos] + l[at] ,
            pre(t[at]) , siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
}
inline void dfs(int pos) {
    static int iid;
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos , rec[id[pos]=++iid] = pos , cs[top[pos]].insert(dis[pos]);
    sgt.update_mx(1,id[pos],dis[pos]-dis[fa[pos]]);
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) swap(x,y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
inline void chain(int x,int lc,const Equation &e) {
    while( top[x] != top[lc] ) {
        sgt.update(1,id[top[x]],id[x],e) ,
        usl[top[x]] = id[top[x]] , usr[top[x]] = max(usr[top[x]],id[x]) , x = fa[top[x]];
    }
    sgt.update(1,id[lc],id[x],e) , usl[top[x]] = id[lc] , usr[top[x]] = max(usr[top[x]],id[x]);
}
inline void reschain(int x,int lc) {
    while( top[x] != top[lc] ) {
        sgt.reset(1,id[top[x]],id[x]) ,
        usl[top[x]] = usr[top[x]] = 0 , x = fa[top[x]];
    }
    sgt.reset(1,id[lc],id[x]) , usl[top[x]] = usr[top[x]] = 0;
}
inline void filla(int u,int v,lli t) { // from u , to v , start time is t .
    int l = lca(u,v);
    if( l == u ) { // fully down .
        Equation e = (Equation){1,t-dis[u]};
        chain(v,u,e);
    } else if( l == v ) {
        Equation e = (Equation){-1,t+dis[u]};
        chain(u,v,e);
    } else {
        const lli tlca = t + dis[u] - dis[l];
        Equation eu = (Equation){-1,t+dis[u]} , ev = (Equation){1,tlca-dis[l]};
        chain(u,l,eu) , chain(v,l,ev);
    }
}
inline void reseta(int u,int v) { // from u , to v , start time is t .
    int l = lca(u,v);
    if( l == u ) reschain(v,u);
    else if( l == v ) reschain(u,v);
    else reschain(u,l) , reschain(v,l);
}
inline bool cross(lli x,lli y,lli xx,lli yy) {
    return x <= yy && xx <= y;
}
inline int coresme(int t,int l,int r,const Equation &e) {
    if( l <= r ) { // have same points .
        lli al = sgt.query(1,l).calc(dis[rec[l]]) , ar = sgt.query(1,r).calc(dis[rec[r]]);
        lli bl = e.calc(dis[rec[l]]) , br = e.calc(dis[rec[r]]);
        if( al == bl && ar == br ) { // sameway .
            return r - l + 1;
        } else if( cross(min(al,ar),max(al,ar),min(bl,br),max(bl,br)) ) {
            const Equation ea = sgt.query(1,l);
            if( ea.k != e.k ) { // may have solution .
                lli lft = ea.k - e.k , rit = e.b - ea.b;
                if( ! ( rit & 1 ) ) {
                    lli sol = rit / lft;
                    if( cs[t].find(sol) != cs[t].end() ) return 1;
                }
            }
        }
    }
    return 0;
}
inline int getsme(int x,int lc,const Equation &e) {
    int ret = 0;
    while( top[x] != top[lc] ) {
        const int t = top[x];
        if( usl[t] && usr[t] ) { // same chain visited .
            int l = max( usl[t] , id[top[x]] ) , r = min( usr[t] , id[x] );
            ret += coresme(t,l,r,e);
        }
        x = fa[top[x]];
    }
    const int t = top[x];
    if( usl[t] && usr[t] ) { // same chain visited .
        int l = max( usl[t] , id[lc] ) , r = min( usr[t] , id[x] );
        ret += coresme(t,l,r,e);
    }
    return ret;
}
inline bool corevis(int t,int l,int r,const Equation &e) {
    if( l <= r ) { // have same points .
        lli al = sgt.query(1,l).calc(dis[rec[l]]) , ar = sgt.query(1,r).calc(dis[rec[r]]);
        lli bl = e.calc(dis[rec[l]]) , br = e.calc(dis[rec[r]]);
        if( cross(min(al,ar),max(al,ar),min(bl,br),max(bl,br)) ) {
            const Equation ea = sgt.query(1,l);
            if( ea.k == e.k ) {
                if( l == r ) return 0;
                const lli deltab = abs(ea.b-e.b) , mxlen = sgt.query_mx(1,l+1,r);
                return deltab < mxlen;
            } else return 1;
        }
    }
    return 0;
}
inline bool used(int x) {
    int t = top[x];
    return usl[t] && usr[t] && usl[t] <= id[x] && id[x] <= usr[t];
}
inline int vevis(int x,const Equation &e) {
    if( used(x) && used(fa[x]) ) {
        Equation ea = sgt.query(1,id[x]);
        lli al = ea.calc(dis[fa[x]]) , ar = ea.calc(dis[x]);
        lli bl = e.calc(dis[fa[x]]) , br = e.calc(dis[x]);
        if( cross(min(al,ar),max(al,ar),min(bl,br),max(bl,br)) ) {
            if( ea.k == e.k ) {
                const lli deltab = abs(ea.b-e.b) , mxlen = dis[x] - dis[fa[x]];
                return deltab < mxlen;
            } else return 1;
        }
    }
    return 0;
}
inline bool getvis(int x,int lc,const Equation &e) {
    while( top[x] != top[lc] ) {
        const int t = top[x];
        if( usl[t] && usr[t] ) { // same chain visited .
            int l = max( usl[t] , id[top[x]] ) , r = min( usr[t] , id[x] );
            if( corevis(t,l,r,e) ) return 1;
        }
        if( vevis(top[x],e) ) return 1;
        x = fa[top[x]]; // how to deal with this edge ? 
    }
    const int t = top[x];
    if( usl[t] && usr[t] ) { // same chain visited .
        int l = max( usl[t] , id[lc] ) , r = min( usr[t] , id[x] );
        if( corevis(t,l,r,e) ) return 1;
    }
    return 0;
}
inline bool queryb(int u,int v,lli t) {
    int l = lca(u,v) , sme = 0;
    if( l == u ) { // fully down .
        Equation e = (Equation){1,t-dis[u]};
        sme = getsme(v,u,e);
        if( sme ) return sme > 1;
        return getvis(v,u,e);
    } else if( l == v ) {
        Equation e = (Equation){-1,t+dis[u]};
        sme = getsme(u,v,e);
        if( sme ) return sme > 1;
        return getvis(u,v,e);
    } else {
        const lli tlca = t + dis[u] - dis[l];
        Equation eu = (Equation){-1,t+dis[u]} , ev = (Equation){1,tlca-dis[l]};
        sme = getsme(u,l,eu) + getsme(v,l,ev);
        if( sme ) return sme > 1;
        return getvis(u,l,eu) || getvis(v,l,ev);
    }
}

int main() {
    freopen("meet.in","r",stdin);
    freopen("meet.out","w",stdout);
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , addedge(b,a,l);
    sgt.build(sgt.cnt=1,1,n) , pre(1) , dfs(1);
    for(int i=1,u,v,t,uu,vv,tt;i<=m;i++) {
        scanf("%d%d%d%d%d%d",&u,&v,&t,&uu,&vv,&tt) , filla(u,v,t);
        puts(queryb(uu,vv,tt)?"YES":"NO") , reseta(u,v);
    }
    fclose(stdout);
    return 0;
}
