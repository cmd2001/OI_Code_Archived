#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=3e5+1e2,maxk=51;
const int mod=998244353;

int rec[maxn];
struct SegmentTree {
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],sum[maxn<<2][maxk],cnt;
    SegmentTree() { cnt = 1 ; }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) {
            sum[pos][0] = 1;
            for(int i=1;i<maxk;i++) sum[pos][i] = (lli) sum[pos][i-1] * rec[ll] % mod;
            return;
        } const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        for(int i=0;i<maxk;i++) sum[pos][i] = ( sum[lson[pos]][i] + sum[rson[pos]][i] ) % mod;
    }
    inline int query(int pos,const int &ll,const int &rr,const int &k) {
        if( ll <= l[pos] && r[pos] <= rr ) return sum[pos][k];
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return query(lson[pos],ll,rr,k);
        else if( ll > mid ) return query(rson[pos],ll,rr,k);
        return ( query(lson[pos],ll,rr,k) + query(rson[pos],ll,rr,k) ) % mod;
    }
}sgt;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],id[maxn];
    inline void addedge(int from,int to) {
        static int cnt = 0;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void pre(int pos) {
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pre(t[at]) , siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
    }
    inline void dfs(int pos) {
        static int iid; rec[id[pos]=++iid] = dep[pos] , top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        if( son[pos] ) dfs(son[pos]);
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
    }
    inline int chain(int x,int y,int k) {
        int ret = 0;
        while( top[x] != top[y] ) {
            if( dep[top[x]] < dep[top[y]] ) std::swap(x,y);
            ret = ( ret + sgt.query(1,id[top[x]],id[x],k) ) % mod , x = fa[top[x]];
        }
        ret = ( ret + sgt.query(1,std::min(id[x],id[y]),std::max(id[x],id[y]),k) ) % mod;
        return ret;
    }
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,m;
    n = getint();
    for(int i=1,a,b;i<n;i++) a = getint() , b = getint() , Tree::addedge(a,b) , Tree::addedge(b,a);
    Tree::pre(1) , Tree::dfs(1) , sgt.build(1,1,n) , scanf("%d",&m);
    for(int i=1,a,b,k;i<=m;i++) a = getint() , b = getint() , k = getint() , printf("%d\n",Tree::chain(a,b,k));
    return 0;
}
