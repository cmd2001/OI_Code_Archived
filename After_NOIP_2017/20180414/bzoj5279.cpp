#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5e4+1e2;
const int inf=0x3f3f3f3f;

int rec[maxn]; // edge id -> segmentree at .

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],miv[maxn<<3],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr , miv[pos] = inf;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void update(int pos,const int &ll,const int &rr,const int &val) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return void(miv[pos]=min(miv[pos],val));
        update(lson[pos],ll,rr,val) , update(rson[pos],ll,rr,val);
    }
    inline int query(int pos,const int &tar) {
        if( l[pos] == r[pos] ) return miv[pos];
        const int mid = r[lson[pos]];
        if( tar <= mid ) return min( miv[pos] , query(lson[pos],tar) );
        else return min( miv[pos] , query(rson[pos],tar) );
    }
}sgt;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],eid[maxn<<1];
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],id[maxn];
    
    inline void coredge(int from,int to,int id) {
        static int cnt = 0;
        t[++cnt] = to , eid[cnt] = id , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void doubledge(int a,int b,int id) {
        coredge(a,b,id) , coredge(b,a,id);
    }
    inline void pre(int pos) {
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]) ,
            siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
    }
    inline void dfs(int pos,int from) {
        static int iid = 0;
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos , rec[from] = id[pos] = ++iid;
        if( son[pos] ) for(int at=s[pos];at;at=nxt[at]) if( t[at] == son[pos] ) { dfs(t[at],eid[at]); break; }
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at],eid[at]);
    }
    inline void chain(int x,int y,int val) {
        while( top[x] != top[y] ) {
            if( dep[top[x]] < dep[top[y]] ) swap(x,y);
            sgt.update(1,id[top[x]],id[x],val) , x = fa[top[x]];
        }
        if( id[x] > id[y] ) swap(x,y);
        if( id[x] != id[y] ) sgt.update(1,id[x]+1,id[y],val);
    }
}

int main() {
    static int n,m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , Tree::doubledge(a,b,i);
    Tree::pre(1) , Tree::dfs(1,0);
    sgt.build(sgt.cnt=1,1,n);
    for(int i=1,a,b,v;i<=m;i++) scanf("%d%d%d",&a,&b,&v) , Tree::chain(a,b,v);
    for(int i=1;i<n;i++) {
        ans = sgt.query(1,rec[i]);
        if( ans == inf ) puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}
